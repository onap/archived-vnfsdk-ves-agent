#pragma once

#include "XQueue.h"
#include "leveldb/db.h"
#include <atomic>
#include <chrono>

namespace vagt
{
    namespace queue
    {
        class XDiskQueue : public XQueue
        {
        public:
            XDiskQueue(const std::string& path);
            ~XDiskQueue();
            virtual bool empty() override;
            virtual XErrorCode push(const std::string & val) override;
            virtual void pop() override;
            virtual std::string front() override;
        private:
            std::string createKey();
            void tryCompact(const std::string& key);

            std::atomic<long> keyId_;
            char key[32];
            std::chrono::system_clock::time_point compactTime_;

            leveldb::DB* db_;
            leveldb::ReadOptions opt_;
            leveldb::Iterator* it_;
        };
    }
}
