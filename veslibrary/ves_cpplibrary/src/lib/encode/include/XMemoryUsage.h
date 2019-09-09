#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XMemoryUsage 
        {
        public:
            XMemoryUsage(const XString& vmIdentifier,
                XNumber memoryFree,
                XNumber memoryUsed);

            virtual void setMemorySwapInAvg(XNumber memorySwapInAvg);
            virtual void setMemorySwapUsedAvg(XNumber memorySwapUsedAvg);
            virtual void setMemorySlabRecl(XNumber memorySlabRecl);
            virtual void setMemorySwapInRateAvg(XNumber memorySwapInRateAvg);
            virtual void setMemoryDemand(XNumber memoryDemand);
            virtual void setMemoryConfigured(XNumber memoryConfigured);
            virtual void setMemorySharedAvg(XNumber memorySharedAvg);
            virtual void setVmIdentifier(const XString& vmIdentifier);
            virtual void setMemoryLatencyAvg(XNumber memoryLatencyAvg);
            virtual void setMemorySwapOutAvg(XNumber memorySwapOutAvg);
            virtual void setMemorySwapOutRateAvg(XNumber memorySwapOutRateAvg);
            virtual void setMemoryFree(XNumber memoryFree);
            virtual void setMemorySlabUnrecl(XNumber memorySlabUnrecl);
            virtual void setMemoryCached(XNumber memoryCached);
            virtual void setMemoryUsed(XNumber memoryUsed);
            virtual void setMemoryBuffered(XNumber memoryBuffered);
            virtual void setPercentMemoryUsage(XNumber percentMemoryUsage);

            std::shared_ptr<XMemoryUsage> imp_;

        protected:
            XMemoryUsage();
        };

        using XArrayOfXMemoryUsage = std::vector<XMemoryUsage>;
    }
}
        