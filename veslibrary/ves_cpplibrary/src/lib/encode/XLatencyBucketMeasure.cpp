#include "XLatencyBucketMeasure.h"
#include "XLatencyBucketMeasureImp.h"

vagt::encode::XLatencyBucketMeasure::XLatencyBucketMeasure()
{
}

vagt::encode::XLatencyBucketMeasure::XLatencyBucketMeasure(XNumber countsInTheBucket):
    imp_(make_shared<XLatencyBucketMeasureImp>(countsInTheBucket))
{
}

void vagt::encode::XLatencyBucketMeasure::setCountsInTheBucket(XNumber countsInTheBucket)
{
    return imp_->setCountsInTheBucket(countsInTheBucket);
}

void vagt::encode::XLatencyBucketMeasure::setHighEndOfLatencyBucket(XNumber highEndOfLatencyBucket)
{
    return imp_->setHighEndOfLatencyBucket(highEndOfLatencyBucket);
}

void vagt::encode::XLatencyBucketMeasure::setLowEndOfLatencyBucket(XNumber lowEndOfLatencyBucket)
{
    return imp_->setLowEndOfLatencyBucket(lowEndOfLatencyBucket);
}
