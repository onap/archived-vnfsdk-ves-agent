#include "XTransportSamples.h"
#include <thread>

using namespace std;
using namespace vagt;
using namespace vagt::encode;
using namespace vagt::queue;
using namespace vagt::transport;
using namespace std::chrono;

void testLibcurlTransport()
{
    auto event = buildFault();

    XTransportOption opt;
    opt.url_ = "http://127.0.0.1:30000";

    auto transport = XTransport::SynchronizedTransport(XTransport::LibCurlTransport(opt));

    transport->start();

    transport->post(event->toString());

    transport->stop();
}

void testRetryTransport()
{
    auto event = buildFault();

    XTransportOption opt;
    opt.url_ = "http://127.0.0.1:30000";

    auto transport = XTransport::RetryTransport(XTransport::LibCurlTransport(opt),
        seconds(1),
        3);

    transport->start();

    transport->post(event->toString());

    transport->stop();
}

void testSwitchableTransport()
{
    auto event = buildFault();

    vector<shared_ptr<XTransport>> transports;

    XTransportOption opt;
    opt.url_ = "http://127.0.0.1:30000";
    auto transport1 = XTransport::RetryTransport(XTransport::LibCurlTransport(opt), 
        seconds(1), 
        3);
    transports.push_back(transport1);

    opt.url_ = "http://127.0.0.1:30001";
    auto transport2 = XTransport::RetryTransport(XTransport::LibCurlTransport(opt), 
        seconds(1), 
        3);
    transports.push_back(transport2);

    auto transport = XTransport::SwitchableTransport(transports);

    transport->start();

    transport->post(event->toString());

    transport->stop();
}

void testMemBufferedTransport()
{
    auto event = buildFault();

    vector<shared_ptr<XTransport>> transports;

    XTransportOption opt;
    opt.url_ = "http://127.0.0.1:30000";
    auto transport1 = XTransport::RetryTransport(XTransport::LibCurlTransport(opt), 
        seconds(1), 
        3);
    transports.push_back(transport1);

    opt.url_ = "http://127.0.0.1:30001";
    auto transport2 = XTransport::RetryTransport(XTransport::LibCurlTransport(opt), 
        seconds(1), 
        3);
    transports.push_back(transport2);

    auto que = XQueue::create(1000);
    auto transport = XTransport::BufferedTransport(XTransport::SwitchableTransport(transports),
        que);

    transport->start();

    for (int i=0; i<1200; i++)
    {
        transport->post(event->toString());
    }

    this_thread::sleep_for(seconds(10));

    transport->stop();
}

void testDiskBufferedTransport()
{
    auto event = buildFault();

    vector<shared_ptr<XTransport>> transports;

    XTransportOption opt;
    opt.url_ = "http://127.0.0.1:30000";
    auto transport1 = XTransport::RetryTransport(XTransport::LibCurlTransport(opt), 
        seconds(1), 
        3);
    transports.push_back(transport1);

    opt.url_ = "http://127.0.0.1:30001";
    auto transport2 = XTransport::RetryTransport(XTransport::LibCurlTransport(opt), 
        seconds(1), 
        3);
    transports.push_back(transport2);

    auto que = XQueue::create("/tmp");
    auto transport = XTransport::BufferedTransport(XTransport::SwitchableTransport(transports),
        que);

    transport->start();

    for (int i=0; i<10; i++)
    {
        transport->post(event->toString());
    }

    this_thread::sleep_for(seconds(10));

    transport->stop();
}

void testRpcClientTransport()
{
    auto event = buildFault();

    XTransportOption rpcOpt;
    rpcOpt.host_ = "127.0.0.1";
    rpcOpt.port_ = 5678;

    auto retryTransport = XTransport::RetryTransport(XTransport::RpcClientTransport(rpcOpt),
        seconds(1),
        3);
    auto transport = XTransport::BufferedTransport(retryTransport, 
        XQueue::create(1000)
        );

    transport->start();

    for (int i=0; i<100; i++)
    {
        transport->post(event->toString());
    }

    this_thread::sleep_for(seconds(10));

    transport->stop();
}

void testRpcServerTransport()
{
    vector<shared_ptr<XTransport>> transports;

    XTransportOption opt;
    opt.url_ = "http://127.0.0.1:30000";
    auto transport1 = XTransport::RetryTransport(XTransport::LibCurlTransport(opt), 
        seconds(1), 
        3);
    transports.push_back(transport1);

    opt.url_ = "http://127.0.0.1:30001";
    auto transport2 = XTransport::RetryTransport(XTransport::LibCurlTransport(opt), 
        seconds(1), 
        3);
    transports.push_back(transport2);

    auto que = XQueue::create("/tmp");
    auto bufferedTransport = XTransport::BufferedTransport(XTransport::SwitchableTransport(transports),
        que);

    XTransportOption rpcOpt;
    rpcOpt.port_ = 5678;

    auto transport = XTransport::RpcServerTransport(bufferedTransport, rpcOpt);

    transport->start();

    this_thread::sleep_for(seconds(10));

    transport->stop();
}
