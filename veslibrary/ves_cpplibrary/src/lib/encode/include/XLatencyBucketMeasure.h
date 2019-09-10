#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XLatencyBucketMeasure 
        {
        public:
            XLatencyBucketMeasure(XNumber countsInTheBucket);

            virtual void setCountsInTheBucket(XNumber countsInTheBucket);
            virtual void setHighEndOfLatencyBucket(XNumber highEndOfLatencyBucket);
            virtual void setLowEndOfLatencyBucket(XNumber lowEndOfLatencyBucket);

            std::shared_ptr<XLatencyBucketMeasure> imp_;

        protected:
            XLatencyBucketMeasure();
        };

        using XArrayOfXLatencyBucketMeasure = std::vector<XLatencyBucketMeasure>;
    }
}
        