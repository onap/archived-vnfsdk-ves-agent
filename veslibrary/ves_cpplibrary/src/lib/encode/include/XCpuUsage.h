#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XCpuUsage 
        {
        public:
            XCpuUsage(const XString& cpuIdentifier,
                XNumber percentUsage);

            virtual void setPercentUsage(XNumber percentUsage);
            virtual void setCpuUsageInterrupt(XNumber cpuUsageInterrupt);
            virtual void setCpuWait(XNumber cpuWait);
            virtual void setCpuCapacityContention(XNumber cpuCapacityContention);
            virtual void setCpuUsageNice(XNumber cpuUsageNice);
            virtual void setCpuDemandMhz(XNumber cpuDemandMhz);
            virtual void setCpuUsageSoftIrq(XNumber cpuUsageSoftIrq);
            virtual void setCpuLatencyAvg(XNumber cpuLatencyAvg);
            virtual void setCpuUsageSteal(XNumber cpuUsageSteal);
            virtual void setCpuDemandPct(XNumber cpuDemandPct);
            virtual void setCpuDemandAvg(XNumber cpuDemandAvg);
            virtual void setCpuIdle(XNumber cpuIdle);
            virtual void setCpuSwapWaitTime(XNumber cpuSwapWaitTime);
            virtual void setCpuUsageSystem(XNumber cpuUsageSystem);
            virtual void setCpuOverheadAvg(XNumber cpuOverheadAvg);
            virtual void setCpuUsageUser(XNumber cpuUsageUser);
            virtual void setCpuIdentifier(const XString& cpuIdentifier);

            std::shared_ptr<XCpuUsage> imp_;

        protected:
            XCpuUsage();
        };

        using XArrayOfXCpuUsage = std::vector<XCpuUsage>;
    }
}
        