#include "XRpcServertTransport.h"
#include "thrift/transport/TServerSocket.h"
#include "thrift/server/TThreadedServer.h"
#include "thrift/protocol/TCompactProtocol.h"
#include "thrift/transport/TBufferTransports.h"
#include "thrift/transport/TSocket.h"
#ifndef SPDLOG_ACTIVE_LEVEL 
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#include "spdlog/spdlog.h"

using namespace std;
using namespace vagt::transport;
using namespace vagt::transport::rpc;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

constexpr auto XRpcServerIdleTime = 60 * 60 * 1000;

class XRpcTransportImp:public XRpcTransportIf 
{
public:
    XRpcTransportImp(XTransport* transport):transport_(transport)
    {
    }

    virtual int16_t post(const std::string & data) override
    {
        if (transport_)
        {
            return transport_->post(data);
        }
    }
private:
    XTransport* transport_;
};

class XRpcTransportFactory : public XRpcTransportIfFactory
{
public:
    XRpcTransportFactory(XTransport* transport):transport_(transport)
    {
    }

    XRpcTransportIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo)
    {
        shared_ptr<TSocket> sock = dynamic_pointer_cast<TSocket>(connInfo.transport);
        if (sock)
        {
            auto pt = new XRpcTransportImp(transport_);
            SPDLOG_INFO("New RPC client connection from:({}:{}), handler:({:x}).", sock->getPeerAddress(), sock->getPeerPort(), (unsigned long)pt);
            return pt;
        }
        return nullptr;
    }

    void releaseHandler(XRpcTransportIf* handler)
    {
        SPDLOG_INFO("Clean RPC client handler:({:x}).", (unsigned long)handler);

        if (handler)
        {
            delete handler;
            handler = nullptr;
        }
    }
private:
    XTransport* transport_;
};

vagt::transport::XRpcServerTransport::XRpcServerTransport(std::shared_ptr<XTransport> transport, const XTransportOption & option):
    transport_(transport),
    option_(option)
{
}

vagt::transport::XRpcServerTransport::~XRpcServerTransport()
{
}

XErrorCode vagt::transport::XRpcServerTransport::start()
{
    if (!transport_)
    {
        SPDLOG_ERROR("Empty transport.");
        return XErrorNok;
    }

    transport_->start();

    startRPC();

    allowPost();

    return XErrorOk;
}

XErrorCode vagt::transport::XRpcServerTransport::stop()
{
    cancelPost();
    if (!transport_)
    {
        SPDLOG_ERROR("Empty transport.");
        return XErrorNok;
    }

    stopRPC();

    future_.get();

    return transport_->stop();
}

XErrorCode vagt::transport::XRpcServerTransport::post(const std::string & event)
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

    return transport_->post(event);
}

void vagt::transport::XRpcServerTransport::cancelPost()
{
    XTransport::cancelPost();

    if (transport_)
    {
        transport_->cancelPost();
    }
}

void vagt::transport::XRpcServerTransport::allowPost()
{
    if (transport_)
    {
        transport_->allowPost();
    }
    XTransport::allowPost();
}

bool vagt::transport::XRpcServerTransport::shouldCancelPost()
{
    return XTransport::shouldCancelPost();
}

XErrorCode vagt::transport::XRpcServerTransport::startRPC()
{
    future_ = std::async(launch::async, [this]() {return this->worker(); });
    return XErrorOk;
}

XErrorCode vagt::transport::XRpcServerTransport::stopRPC()
{
    if (rpcServer_)
    {
        rpcServer_->stop();
    }
    return XErrorOk;
}

void vagt::transport::XRpcServerTransport::worker()
{
    string source("0.0.0.0");
    if (!option_.sourceIp_.empty())
    {
        source = option_.sourceIp_;
    }

    int port = 5678;
    if (option_.port_ > 1024)
    {
        port = option_.port_;
    }

    SPDLOG_INFO("Start RPC transport thread:({}:{}).", source, port);

    auto serverSocket = make_shared<TServerSocket>(source, port);
    serverSocket->setRecvTimeout(XRpcServerIdleTime);
    rpcServer_ = make_shared<TThreadedServer>(
        make_shared<XRpcTransportProcessorFactory>(make_shared<XRpcTransportFactory>(this)),
        serverSocket,
        make_shared<TBufferedTransportFactory>(),
        make_shared<TCompactProtocolFactory>());

    while (!shouldCancelPost())
    {
        try
        {
            rpcServer_->serve();
        }
        catch (apache::thrift::TException ex)
        {
            SPDLOG_ERROR("{}", ex.what());
            this_thread::sleep_for(chrono::seconds(1));
            continue;
        }
        catch (...)
        {
            SPDLOG_ERROR("Unknown Exception in thrift.");
            this_thread::sleep_for(chrono::seconds(1));
            continue;
        }
    }

    SPDLOG_INFO("Quit RPC transport thread.");
}
