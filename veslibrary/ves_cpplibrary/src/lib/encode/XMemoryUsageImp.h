#pragma once
        
#include "XMemoryUsage.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XMemoryUsageImp : public XMemoryUsage, public XJsonable
        {
        public:
            XMemoryUsageImp(const XString& vmIdentifier,
                XNumber memoryFree,
                XNumber memoryUsed);

            virtual json toJson() override;

            virtual void setMemorySwapInAvg(XNumber memorySwapInAvg) override ;
            virtual void setMemorySwapUsedAvg(XNumber memorySwapUsedAvg) override ;
            virtual void setMemorySlabRecl(XNumber memorySlabRecl) override ;
            virtual void setMemorySwapInRateAvg(XNumber memorySwapInRateAvg) override ;
            virtual void setMemoryDemand(XNumber memoryDemand) override ;
            virtual void setMemoryConfigured(XNumber memoryConfigured) override ;
            virtual void setMemorySharedAvg(XNumber memorySharedAvg) override ;
            virtual void setVmIdentifier(const XString& vmIdentifier) override ;
            virtual void setMemoryLatencyAvg(XNumber memoryLatencyAvg) override ;
            virtual void setMemorySwapOutAvg(XNumber memorySwapOutAvg) override ;
            virtual void setMemorySwapOutRateAvg(XNumber memorySwapOutRateAvg) override ;
            virtual void setMemoryFree(XNumber memoryFree) override ;
            virtual void setMemorySlabUnrecl(XNumber memorySlabUnrecl) override ;
            virtual void setMemoryCached(XNumber memoryCached) override ;
            virtual void setMemoryUsed(XNumber memoryUsed) override ;
            virtual void setMemoryBuffered(XNumber memoryBuffered) override ;
            virtual void setPercentMemoryUsage(XNumber percentMemoryUsage) override ;

        private:
            //required
            XString vmIdentifier_;
            XNumber memoryFree_;
            XNumber memoryUsed_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        