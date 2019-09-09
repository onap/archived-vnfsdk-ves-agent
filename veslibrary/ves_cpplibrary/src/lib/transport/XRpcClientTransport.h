#pragma once

#include "XTransport.h"
#include "thrift/transport/TSocket.h"
#include "thrift/protocol/TCompactProtocol.h"
#include "thrift/transport/TBufferTransports.h"
#include "gen-cpp/rpc_constants.h"
#include "gen-cpp/rpc_types.h"
#include "gen-cpp/XRpcTransport.h"

namespace vagt
{
    namespace transport
    {
        class XRpcClientTransport : public XTransport
        {
        public:
            XRpcClientTransport(const XTransportOption& option);
            virtual ~XRpcClientTransport();

            virtual XErrorCode start() override;
            virtual XErrorCode stop() override;
            virtual XErrorCode post(const std::string& event) override;

            virtual void cancelPost() override;
            virtual void allowPost() override;
            virtual bool shouldCancelPost() override;
        private:
            XErrorCode startRPC();
            XErrorCode stopRPC();

            XTransportOption option_;

            std::shared_ptr<apache::thrift::transport::TTransport> rpcTransport_;
            std::shared_ptr<vagt::transport::rpc::XRpcTransportClient> rpcClient_;
        };
    }
}
