#include "XMemQueue.h"
#ifndef SPDLOG_ACTIVE_LEVEL 
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#include "spdlog/spdlog.h"

using namespace std;
using namespace vagt::queue;

vagt::queue::XMemQueue::XMemQueue(int capacity):capacity_(capacity),size_(0)
{

}

bool vagt::queue::XMemQueue::empty()
{
    return 0 == size_;
}

XErrorCode vagt::queue::XMemQueue::push(const std::string & val)
{
    if (size_ >= capacity_)
    {
        queue_.pop();
        SPDLOG_WARN("Drop from queue.");
        size_--;
    }

    queue_.push(val);
    size_++;

    return XErrorOk;
}

void vagt::queue::XMemQueue::pop()
{
    //cal empty() before cal pop()
    queue_.pop();
    size_--;
}

std::string vagt::queue::XMemQueue::front()
{
    //cal empty() before cal pop()
    return queue_.front();
}
