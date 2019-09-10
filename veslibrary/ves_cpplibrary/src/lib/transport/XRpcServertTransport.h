#pragma once

#include "XTransport.h"
#include "thrift/server/TServer.h"
#include "gen-cpp/rpc_constants.h"
#include "gen-cpp/rpc_types.h"
#include "gen-cpp/XRpcTransport.h"
#include <future>

namespace vagt
{
    namespace transport
    {
        class XRpcServerTransport : public XTransport
        {
        public:
            XRpcServerTransport(std::shared_ptr<XTransport> transport, const XTransportOption& option);
            virtual ~XRpcServerTransport();

            virtual XErrorCode start() override;
            virtual XErrorCode stop() override;
            virtual XErrorCode post(const std::string& event) override;

            virtual void cancelPost() override;
            virtual void allowPost() override;
            virtual bool shouldCancelPost() override;
        private:
            XErrorCode startRPC();
            XErrorCode stopRPC();
            void worker();
            std::future<void> future_;

            std::shared_ptr<XTransport> transport_;
            XTransportOption option_;

            std::shared_ptr<apache::thrift::server::TServer> rpcServer_;
        };
    }
}
