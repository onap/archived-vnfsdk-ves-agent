#pragma once

#include "XTransport.h"
#include "XQueue.h"
#include <future>
#include <mutex>
#include <condition_variable>

namespace vagt
{
    namespace transport
    {
        class XBufferedTransport : public XTransport
        {
        public:
            XBufferedTransport(std::shared_ptr<XTransport> transport, std::shared_ptr<vagt::queue::XQueue> queue);
            virtual ~XBufferedTransport();

            virtual XErrorCode start() override;
            virtual XErrorCode stop() override;
            virtual XErrorCode post(const std::string& event) override;

            virtual void cancelPost() override;
            virtual void allowPost() override;
            virtual bool shouldCancelPost() override;

        private:
            void worker();

            std::shared_ptr<XTransport> transport_;
            std::shared_ptr<queue::XQueue> queue_;
            std::future<void> future_;

            std::condition_variable cond_;
            std::mutex lock_;
        };
    }
}
 
