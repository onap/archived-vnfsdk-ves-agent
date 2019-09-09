#pragma once

#include <vector>
#include "XTransport.h"

namespace vagt
{
    namespace transport
    {
        class XSwitchableTransport : public XTransport
        {
        public:
            XSwitchableTransport(std::vector<std::shared_ptr<XTransport>>& processors);

            virtual ~XSwitchableTransport() {}

            virtual XErrorCode start() override;

            virtual XErrorCode stop() override;

            virtual XErrorCode post(const std::string& event) override;

            virtual void cancelPost() override;

            virtual void allowPost() override;

            virtual bool shouldCancelPost() override;

        private:
            XErrorCode tryTransport(const std::string& event);
            void switchTransport(vagt::transport::XErrorCode reason);

            std::vector<std::shared_ptr<XTransport>> transports_;
            unsigned int transportIndex_;
        };
    }
}
