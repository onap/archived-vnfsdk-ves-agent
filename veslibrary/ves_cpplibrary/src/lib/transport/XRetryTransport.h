#pragma once

#include <chrono>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include "XTransport.h"

namespace vagt
{
    namespace transport
    {
        class XRetryTransport : public XTransport
        {
        public:
            XRetryTransport(std::shared_ptr<XTransport> transport, std::chrono::milliseconds retryInterval, int retryTimes);

            virtual ~XRetryTransport() {}

            virtual XErrorCode start() override;

            virtual XErrorCode stop() override;

            virtual XErrorCode post(const std::string& event) override;

            virtual void cancelPost() override;

            virtual void allowPost() override;

            virtual bool shouldCancelPost() override;

        private:
            std::shared_ptr<XTransport> transport_;
            std::chrono::milliseconds retryInterval_;
            int tryTimes_;

            std::atomic<bool> isRetryRunning_;

            std::mutex lock_;
            std::condition_variable cond_;
        };
    }
}