#include "XBufferedTransport.h"
#ifndef SPDLOG_ACTIVE_LEVEL 
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#include "spdlog/spdlog.h"

using namespace std;
using namespace vagt::transport;
using namespace spdlog;

vagt::transport::XBufferedTransport::XBufferedTransport(std::shared_ptr<XTransport> transport, std::shared_ptr<queue::XQueue> queue):
    transport_(transport), queue_(queue)
{
}

vagt::transport::XBufferedTransport::~XBufferedTransport()
{
}

XErrorCode vagt::transport::XBufferedTransport::start()
{
    if (!transport_)
    {
        SPDLOG_ERROR("Empty transport.");
        return XErrorNok;
    }

    if (!queue_)
    {
        SPDLOG_ERROR("Empty queue.");
        return XErrorNok;
    }

    auto rc = transport_->start();

    future_ = async(launch::async, [this]() {return this->worker(); });

    allowPost();

    return rc;
}

XErrorCode vagt::transport::XBufferedTransport::stop()
{
    cancelPost();
    if (!transport_)
    {
        SPDLOG_ERROR("Empty transport.");
        return XErrorNok;
    }

    if (!queue_)
    {
        SPDLOG_ERROR("Empty queue.");
        return XErrorNok;
    }

    future_.get();

    return transport_->stop();
}

XErrorCode vagt::transport::XBufferedTransport::post(const std::string& event)
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

    if (!queue_)
    {
        return XErrorNok;
    }

    auto rc = vagt::queue::XErrorOk;
    {
        unique_lock<mutex> _(lock_);
        rc = queue_->push(event);
        cond_.notify_one();
    }
   
    if (rc == vagt::queue::XErrorOk)
    {
        return XErrorOk;
    }
    else
    {
        return XErrorNok;
    }
}

void vagt::transport::XBufferedTransport::cancelPost()
{
    XTransport::cancelPost();

    {
        unique_lock<mutex> _(lock_);
        cancel_.store(true, std::memory_order_release);
        cond_.notify_one();
    }

    if (transport_)
    {
        transport_->cancelPost();
    }
}

void vagt::transport::XBufferedTransport::allowPost()
{
    if (transport_)
    {
        transport_->allowPost();
    }
    XTransport::allowPost();
}

bool vagt::transport::XBufferedTransport::shouldCancelPost()
{
    return XTransport::shouldCancelPost();
}

void vagt::transport::XBufferedTransport::worker()
{
    SPDLOG_INFO("Start transport send thread.");
    while (true)
    {
        string event;
        {
            unique_lock<mutex> _(lock_);
            cond_.wait(_, [this]() {return shouldCancelPost() || !queue_->empty(); });

            if (shouldCancelPost())
            {
                SPDLOG_INFO("Quit transport send thread.");
                return;
            }

            if (!queue_->empty())
            {
                event = queue_->front();
            }
            else
            {
                continue;
            }
        }

        if (transport_)
        {
            auto rc = transport_->post(event);
            if (vagt::transport::XErrorOk == rc)
            {
                unique_lock<mutex> _(lock_);
                queue_->pop();
            }
            else if (vagt::transport::XErrorClientError == rc)
            {
                unique_lock<mutex> _(lock_);
                queue_->pop();
                SPDLOG_WARN("Drop event:({}) ({}).", event, rc);
            }
        }
    }
}
