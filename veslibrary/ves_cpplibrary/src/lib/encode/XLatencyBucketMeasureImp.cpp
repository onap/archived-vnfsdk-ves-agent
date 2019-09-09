#include "XLatencyBucketMeasureImp.h"

XLatencyBucketMeasureImp::XLatencyBucketMeasureImp(XNumber countsInTheBucket):
        countsInTheBucket_(countsInTheBucket)
{

}

void XLatencyBucketMeasureImp::setCountsInTheBucket(XNumber countsInTheBucket)
{
    comVals_["countsInTheBucket"] = countsInTheBucket;
}
            
void XLatencyBucketMeasureImp::setHighEndOfLatencyBucket(XNumber highEndOfLatencyBucket)
{
    comVals_["highEndOfLatencyBucket"] = highEndOfLatencyBucket;
}
            
void XLatencyBucketMeasureImp::setLowEndOfLatencyBucket(XNumber lowEndOfLatencyBucket)
{
    comVals_["lowEndOfLatencyBucket"] = lowEndOfLatencyBucket;
}

json XLatencyBucketMeasureImp::toJson()
{
    try
    {
        json field = {
            {"countsInTheBucket", countsInTheBucket_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XLatencyBucketMeasure to json object:{}.", e.what());
        return json();
    }
}
            