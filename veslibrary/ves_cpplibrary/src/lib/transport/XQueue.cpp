#include "XQueue.h"
#include "XMemQueue.h"
#include "XDiskQueue.h"

using namespace vagt::queue;

std::shared_ptr<XQueue> vagt::queue::XQueue::create(int capacity)
{
    return std::make_shared<XMemQueue>(capacity);
}

std::shared_ptr<XQueue> vagt::queue::XQueue::create(const std::string & path)
{
    return std::make_shared<XDiskQueue>(path);
}
