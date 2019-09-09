#include "XRetryTransport.h"
#ifndef SPDLOG_ACTIVE_LEVEL 
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#include "spdlog/spdlog.h"

using namespace std;
using namespace vagt;
using namespace vagt::transport;
using namespace spdlog;

XRetryTransport::XRetryTransport(std::shared_ptr<XTransport> transport, std::chrono::milliseconds retryInterval, int tryTimes):
    transport_(transport),
    retryInterval_(retryInterval),
    tryTimes_(tryTimes),
    isRetryRunning_(false)
{
}

XErrorCode XRetryTransport::start()
{
    if (!transport_)
    {
        SPDLOG_ERROR("Empty transport.");
        return XErrorNok;
    }

     auto rc = transport_->start();

     allowPost();

     return rc;
}

XErrorCode XRetryTransport::stop()
{
    cancelPost();
    if (!transport_)
    {
        SPDLOG_ERROR("Empty transport.");
        return XErrorNok;
    }

    while (isRetryRunning_.load(std::memory_order_acquire))
    {
        SPDLOG_DEBUG("Waiting for retry exit.");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return transport_->stop();
}

XErrorCode XRetryTransport::post(const std::string& event)
{
    if (shouldCancelPost())
    {
        return XErrorCanceled;
    }

    if (event.empty())
    {
        SPDLOG_WARN("Trying post empty event.");
        return XErrorClientError;
    }

    if (!transport_)
    {
        SPDLOG_ERROR("Empty transport.");
        return XErrorNok;
    }

    XErrorCode rc = XErrorNok;

    isRetryRunning_.store(true, std::memory_order_release);

	int idx = 0;
    do
    {
        SPDLOG_DEBUG("Posting event:{}.", event);
        rc = transport_->post(event);
        SPDLOG_DEBUG("Post event:{} ({}).", event, rc);
        if (rc == XErrorOk || rc == XErrorCanceled)
        {
            isRetryRunning_.store(false, std::memory_order_release);
            return rc;
        }
        else if (rc == XErrorClientError)
        {
            isRetryRunning_.store(false, std::memory_order_release);
            SPDLOG_ERROR("Post event:({}).", rc);
            return rc;
        }
        //else if (rc == XErrorTimeout || rc == XErrorServerError || rc == XErrorNetworkError)
        else 
        {
            ++idx;
            if (shouldCancelPost() || idx>=tryTimes_)
            {
                break;
            }

            SPDLOG_INFO("Stopping transport for retry:({}), time:({}).", rc, idx);
            transport_->stop();
            {
                unique_lock<mutex> lk(lock_);
                bool cancel = cond_.wait_for(lk, retryInterval_, [this]() { return this->cancel_.load(); });
                if (cancel)
                {
                    isRetryRunning_.store(false, std::memory_order_release);
                    SPDLOG_INFO("Cancel post event:({}).", rc);
                    return rc;
                }
            }

            SPDLOG_INFO("Starting transport for retry:({}), time:({}).", rc, idx);
            transport_->start();
        }
    }
    while(true);


    isRetryRunning_.store(false, std::memory_order_release);
    SPDLOG_ERROR("Post event:({}).", rc);
    return rc;
}

void vagt::transport::XRetryTransport::cancelPost()
{
    XTransport::cancelPost();

    {
        unique_lock<mutex> lk(lock_);
        cancel_.store(true, std::memory_order_release);
        cond_.notify_one();
    }

    if (transport_)
    {
        transport_->cancelPost();
    }
}

void vagt::transport::XRetryTransport::allowPost()
{
    if (transport_)
    {
        transport_->allowPost();
    }
    XTransport::allowPost();
}

bool vagt::transport::XRetryTransport::shouldCancelPost()
{
    return XTransport::shouldCancelPost();
}

