#pragma once
        
#include "XCpuUsage.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XCpuUsageImp: public XCpuUsage, public XJsonable
        {
        public:
            XCpuUsageImp(const XString& cpuIdentifier,
                XNumber percentUsage);

            virtual json toJson() override;

            virtual void setPercentUsage(XNumber percentUsage) override;
            virtual void setCpuUsageInterrupt(XNumber cpuUsageInterrupt) override;
            virtual void setCpuWait(XNumber cpuWait) override;
            virtual void setCpuCapacityContention(XNumber cpuCapacityContention) override;
            virtual void setCpuUsageNice(XNumber cpuUsageNice) override;
            virtual void setCpuDemandMhz(XNumber cpuDemandMhz) override;
            virtual void setCpuUsageSoftIrq(XNumber cpuUsageSoftIrq) override;
            virtual void setCpuLatencyAvg(XNumber cpuLatencyAvg) override;
            virtual void setCpuUsageSteal(XNumber cpuUsageSteal) override;
            virtual void setCpuDemandPct(XNumber cpuDemandPct) override;
            virtual void setCpuDemandAvg(XNumber cpuDemandAvg) override;
            virtual void setCpuIdle(XNumber cpuIdle) override;
            virtual void setCpuSwapWaitTime(XNumber cpuSwapWaitTime) override;
            virtual void setCpuUsageSystem(XNumber cpuUsageSystem) override;
            virtual void setCpuOverheadAvg(XNumber cpuOverheadAvg) override;
            virtual void setCpuUsageUser(XNumber cpuUsageUser) override;
            virtual void setCpuIdentifier(const XString& cpuIdentifier) override;

        private:
            //required
            XNumber percentUsage_;
            XString cpuIdentifier_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        