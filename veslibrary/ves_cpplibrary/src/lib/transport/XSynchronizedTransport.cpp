#include "XSynchronizedTransport.h"
#ifndef SPDLOG_ACTIVE_LEVEL 
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#include "spdlog/spdlog.h"

using namespace std;
using namespace vagt;
using namespace vagt::transport;

XSynchronizedTransport::XSynchronizedTransport(std::shared_ptr<XTransport> transport):
    transport_(transport),
    status_(XStopped)
{
}

XErrorCode XSynchronizedTransport::start()
{
    unique_lock<mutex> lk(controlLock_);

    if (status_ == XStarted)
    {
        return XErrorOk;
    }

    XErrorCode rc = XErrorNok;
    if (transport_)
    {
        rc = transport_->start();
    }

    if (rc == XErrorOk)
    {
        status_ = XStarted;
    }

    allowPost();

    return rc;
}

XErrorCode XSynchronizedTransport::stop()
{
    unique_lock<mutex> lk(controlLock_);

    if (status_ == XStopped)
    {
        return XErrorOk;
    }

    cancelPost();

    if (transport_)
    {
        transport_->cancelPost();
    }

    unique_lock<mutex> lkPost(postLock_);
    XErrorCode rc = XErrorNok;
    if (transport_)
    {
        rc = transport_->stop();
    }

    if (rc == XErrorOk)
    {
        status_ = XStopped;
    }
    return rc;
}

XErrorCode XSynchronizedTransport::post(const std::string& event)
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

    unique_lock<mutex> lk(postLock_);
    if (transport_)
    {
        return transport_->post(event);
    }
    return XErrorNok;
}

void XSynchronizedTransport::cancelPost()
{
    XTransport::cancelPost();

    if (transport_)
    {
        transport_->cancelPost();
    }
}

void XSynchronizedTransport::allowPost()
{
    if (transport_)
    {
        transport_->allowPost();
    }
    XTransport::allowPost();
}

bool XSynchronizedTransport::shouldCancelPost()
{
    return XTransport::shouldCancelPost();
}
