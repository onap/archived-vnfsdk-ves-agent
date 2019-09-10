#pragma once

#include "XQueue.h"
#include <queue>

namespace vagt
{
    namespace queue
    {
        class XMemQueue: public XQueue
        {
        public:
            XMemQueue(int capacity);
            virtual bool empty() override;
            virtual XErrorCode push(const std::string & val) override;
            virtual void pop() override;
            virtual std::string front() override;
        private:
            int capacity_;
            int size_;
            std::queue<std::string> queue_;
        };
    }
}
