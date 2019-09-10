#pragma once
#include <mutex>
#include "XTransport.h"

namespace vagt
{
    namespace transport
    {
        class XSynchronizedTransport : public XTransport
        {
        public:
            enum XStatus : unsigned short
            {
                XStarted,
                XStopped,
            };

            XSynchronizedTransport(std::shared_ptr<XTransport> transport);

            virtual ~XSynchronizedTransport() {}

            virtual XErrorCode start() override;

            virtual XErrorCode stop() override;

            virtual XErrorCode post(const std::string& event) override;

            virtual void cancelPost() override;

            virtual void allowPost() override;

            virtual bool shouldCancelPost() override;

        private:
            std::mutex postLock_;
            std::mutex controlLock_;
            std::shared_ptr<XTransport> transport_;
            XStatus status_;
        };
    }
}
