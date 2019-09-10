#pragma once
        
#include "XLatencyBucketMeasure.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XLatencyBucketMeasureImp : public XLatencyBucketMeasure, public XJsonable
        {
        public:
            XLatencyBucketMeasureImp(XNumber countsInTheBucket);

            virtual json toJson() override;

            virtual void setCountsInTheBucket(XNumber countsInTheBucket) override;
            virtual void setHighEndOfLatencyBucket(XNumber highEndOfLatencyBucket) override;
            virtual void setLowEndOfLatencyBucket(XNumber lowEndOfLatencyBucket) override;

        private:
            //required
            XNumber countsInTheBucket_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        