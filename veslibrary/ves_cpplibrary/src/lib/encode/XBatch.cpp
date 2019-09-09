#include "XBatch.h"
#include "XBatchImp.h"

std::shared_ptr<XBatch> vagt::encode::XBatch::create()
{
    return std::make_shared<XBatchImp>();
}
