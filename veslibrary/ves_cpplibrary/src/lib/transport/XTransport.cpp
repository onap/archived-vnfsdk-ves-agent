#include "XTransport.h"
#include "XLibcurlTransport.h"
#include "XRetryTransport.h"
#include "XSwitchableTransport.h"
#include "XSynchronizedTransport.h"
#include "XBufferedTransport.h"
#include "XRpcClientTransport.h"
#include "XRpcServertTransport.h"

using namespace vagt::transport;

XTransport::XTransport():cancel_(true)
{
}

void XTransport::cancelPost()
{
    cancel_.store(true, std::memory_order_release);
}

void XTransport::allowPost()
{
    cancel_.store(false, std::memory_order_release);
}

bool XTransport::shouldCancelPost()
{
    return cancel_.load(std::memory_order_acquire);
}

std::shared_ptr<XTransport> vagt::transport::XTransport::LibCurlTransport(const XTransportOption & option)
{
    return std::make_shared<XLibcurlTransport>(option);
}

std::shared_ptr<XTransport> vagt::transport::XTransport::RetryTransport(std::shared_ptr<XTransport> transport, std::chrono::milliseconds retryInterval, int retryTimes)
{
    return std::make_shared<XRetryTransport>(transport, retryInterval, retryTimes);
}

std::shared_ptr<XTransport> vagt::transport::XTransport::SwitchableTransport(std::vector<std::shared_ptr<XTransport>>& transports)
{
    return std::make_shared<XSwitchableTransport>(transports);
}

std::shared_ptr<XTransport> vagt::transport::XTransport::SynchronizedTransport(std::shared_ptr<XTransport> transport)
{
    return std::make_shared<XSynchronizedTransport>(transport);
}

std::shared_ptr<XTransport> vagt::transport::XTransport::BufferedTransport(std::shared_ptr<XTransport> transport, std::shared_ptr<vagt::queue::XQueue> queue)
{
    return std::make_shared<XBufferedTransport>(transport, queue);
}

std::shared_ptr<XTransport> vagt::transport::XTransport::RpcClientTransport(const XTransportOption& option)
{
    return std::make_shared<XRpcClientTransport>(option);
}

std::shared_ptr<XTransport> vagt::transport::XTransport::RpcServerTransport(std::shared_ptr<XTransport> transport, const XTransportOption& option)
{
    return std::make_shared<XRpcServerTransport>(transport, option);
}
