#include "XDiskQueue.h"
#ifndef SPDLOG_ACTIVE_LEVEL 
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#include "spdlog/spdlog.h"
#include "leveldb/env.h"

using namespace std;
using namespace vagt::queue;
using namespace leveldb;

constexpr auto XDiskQueueCompactInterval = 1800;

class XDummyLogger : public leveldb::Logger
{
    void Logv(const char* format, va_list ap) {}
};

vagt::queue::XDiskQueue::XDiskQueue(const std::string & path):db_(nullptr),it_(nullptr),keyId_(0)
{
    compactTime_ = chrono::system_clock::now();

    Options opt;
    opt.create_if_missing = true;
    opt.write_buffer_size = 4 * 1024 * 1024;
    opt.max_open_files = 10;
    opt.info_log = new XDummyLogger;

    opt_.fill_cache = true;

    Status status = DB::Open(opt, path, &db_);
    if (status.ok() && db_ != nullptr)
    {
        SPDLOG_INFO("Disk queue is ready.");
        return;
    }

    SPDLOG_INFO("Repairing disk queue.");
    status = RepairDB(path, opt);
    if (status.ok())
    {
        status = DB::Open(opt, path.c_str(), &db_);
        if (status.ok() && db_ != nullptr)
        {
            SPDLOG_INFO("Disk queue is ready.");
            return;
        }
    }

    SPDLOG_ERROR("Fail to initialize disk queue:{}.", status.ToString());
}

vagt::queue::XDiskQueue::~XDiskQueue()
{
    if (it_)
    {
        delete it_;
        it_ = nullptr;
    }

    if (db_)
    {
        delete db_;
        db_ = nullptr;
    }
}

bool vagt::queue::XDiskQueue::empty()
{
    if (!it_)
    {
        it_ = db_->NewIterator(opt_);
        it_->SeekToFirst();
        if (it_->Valid())
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    if (it_->Valid())
    {
        return false;
    }

    delete it_;
    it_ = db_->NewIterator(opt_);
    it_->SeekToFirst();
    if (it_->Valid())
    {
        return false;
    }
    else
    {
        return true;
    }
}

XErrorCode vagt::queue::XDiskQueue::push(const std::string & val)
{
    auto key = createKey();
    SPDLOG_DEBUG("Push {} to disk queue:{}.", val, key);

    WriteOptions opt;
    opt.sync = false;
    auto status = db_->Put(opt, key, val);
    if (!status.ok())
    {
        SPDLOG_ERROR("Fail to push {} to disk queue:{}.", key, status.ToString());
        return XErrorNok;
    }

    return XErrorOk;
}

void vagt::queue::XDiskQueue::pop()
{
    if (!it_ || !it_->Valid())
    {
        SPDLOG_ERROR("Iterator is not valid.");
        return;
    }

    auto delKey = it_->key().ToString();
    it_->Next();

    WriteOptions wo;
    wo.sync = false;

    auto status = db_->Delete(wo, delKey);
    if (status.ok())
    {
        SPDLOG_DEBUG("Pop {} from disk queue.", delKey);

        tryCompact(delKey);

        return;
    }
    else
    {
        SPDLOG_ERROR("Fail to pop {} from disk queue:{}.", delKey, status.ToString());
        return;
    }
}

std::string vagt::queue::XDiskQueue::front()
{
    if (it_ && it_->Valid())
    {
        return it_->value().ToString();
    }

    SPDLOG_ERROR("Iterator is not valid.");
    return "";
}

std::string vagt::queue::XDiskQueue::createKey()
{
    auto now = chrono::system_clock::now().time_since_epoch().count();
    snprintf(key, sizeof(key), "%020ld_%010ld", now, keyId_.fetch_add(1));
    return key;
}

void vagt::queue::XDiskQueue::tryCompact(const std::string & key)
{
    if (it_->Valid())
    {
        return;
    }

    delete it_;
    it_ = nullptr;

    auto now = chrono::system_clock::now();
    auto duration = chrono::duration_cast<std::chrono::seconds>(now - compactTime_).count();

    if (duration > XDiskQueueCompactInterval &&
        db_ &&
        !key.empty())
    {
        SPDLOG_INFO("Disk queue compaction starting...");
        Slice end(key);
        SPDLOG_INFO("Compact key older than {}.", end.ToString());
        db_->CompactRange(NULL, &end);
        SPDLOG_INFO("Disk queue compaction complete...");

        compactTime_ = now;
    }
}
