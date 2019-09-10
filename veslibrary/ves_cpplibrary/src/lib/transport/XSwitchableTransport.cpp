#include "XSwitchableTransport.h"
#ifndef SPDLOG_ACTIVE_LEVEL 
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#include "spdlog/spdlog.h"

using namespace std;
using namespace vagt;
using namespace vagt::transport;

XSwitchableTransport::XSwitchableTransport(std::vector<std::shared_ptr<XTransport>>& processors):
    transports_(processors),
    transportIndex_(0)
{
}

void XSwitchableTransport::cancelPost()
{
    XTransport::cancelPost();
    for (auto transport : transports_)
    {
        if (transport)
        {
            transport->cancelPost();
        }
    }
}

void XSwitchableTransport::allowPost()
{
    for (auto transport : transports_)
    {
        if (transport)
        {
            transport->allowPost();
        }
    }
    XTransport::allowPost();
}

bool XSwitchableTransport::shouldCancelPost()
{
    return XTransport::shouldCancelPost();
}

XErrorCode XSwitchableTransport::tryTransport(const std::string& event)
{
    auto transport = transports_[transportIndex_];
    if (!transport)
    {
        SPDLOG_ERROR("Empty transport.");
        return XErrorNok;
    }

    SPDLOG_DEBUG("Transport({}) posting event:{}.", transportIndex_, event);
    return transport->post(event);
}

void XSwitchableTransport::switchTransport(XErrorCode reason)
{
    SPDLOG_INFO("Switching transport:({}).", reason);

    auto transport = transports_[transportIndex_];
    if (!transport)
    {
        SPDLOG_ERROR("Empty transport.");
        return;
    }

    transport->stop();

    ++transportIndex_;
    if (transportIndex_ >= transports_.size())
    {
        transportIndex_ = 0;
    }

    SPDLOG_INFO("Switch to transport, index:({}).", transportIndex_);
    transport = transports_[transportIndex_];
    if (!transport)
    {
        SPDLOG_ERROR("Empty transport({}).", transportIndex_);
        return;
    }

    transport->start();
}

XErrorCode XSwitchableTransport::start()
{
    if (transportIndex_ >= transports_.size())
    {
        SPDLOG_ERROR("Transport index ({}) >= transport number ({}).", transportIndex_, transports_.size());
        return XErrorNok;
    }

    auto transport = transports_[transportIndex_];
    XErrorCode rc = XErrorNok;
    if (transport)
    {
        rc = transport->start();
    }

    allowPost();

    return rc;
}

XErrorCode XSwitchableTransport::stop()
{
    cancelPost();

    if (transportIndex_ >= transports_.size())
    {
        SPDLOG_ERROR("Transport index ({}) >= transport number ({}).", transportIndex_, transports_.size());
        return XErrorNok;
    }

    auto transport = transports_[transportIndex_];
    XErrorCode rc = XErrorNok;
    if (transport)
    {
        rc = transport->stop();
    }

    return rc;
}

XErrorCode XSwitchableTransport::post(const std::string& event)
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

    if (transportIndex_ >= transports_.size())
    {
        SPDLOG_ERROR("Transport index ({}) >= transport number ({}).", transportIndex_, transports_.size());
        return XErrorNok;
    }

    auto rc = XErrorNok;
    for (auto i = 0;
        !shouldCancelPost() && i < transports_.size();
        ++i)
    {
        rc = tryTransport(event);
        if (rc == XErrorOk ||
            rc == XErrorClientError ||
            rc == XErrorCanceled)
        {
            return rc;
        }
        else
        {
            if (shouldCancelPost())
            {
                break;
            }
            switchTransport(rc);
        }
    }

    return rc;
}

