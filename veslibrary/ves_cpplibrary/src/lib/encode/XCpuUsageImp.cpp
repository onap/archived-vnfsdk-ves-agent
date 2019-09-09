#include "XCpuUsageImp.h"

XCpuUsageImp::XCpuUsageImp(const XString& cpuIdentifier,
    XNumber percentUsage):
        cpuIdentifier_(cpuIdentifier),
        percentUsage_(percentUsage)
{

}

void XCpuUsageImp::setPercentUsage(XNumber percentUsage)
{
    comVals_["percentUsage"] = percentUsage;
}
            
void XCpuUsageImp::setCpuUsageInterrupt(XNumber cpuUsageInterrupt)
{
    comVals_["cpuUsageInterrupt"] = cpuUsageInterrupt;
}
            
void XCpuUsageImp::setCpuWait(XNumber cpuWait)
{
    comVals_["cpuWait"] = cpuWait;
}
            
void XCpuUsageImp::setCpuCapacityContention(XNumber cpuCapacityContention)
{
    comVals_["cpuCapacityContention"] = cpuCapacityContention;
}
            
void XCpuUsageImp::setCpuUsageNice(XNumber cpuUsageNice)
{
    comVals_["cpuUsageNice"] = cpuUsageNice;
}
            
void XCpuUsageImp::setCpuDemandMhz(XNumber cpuDemandMhz)
{
    comVals_["cpuDemandMhz"] = cpuDemandMhz;
}
            
void XCpuUsageImp::setCpuUsageSoftIrq(XNumber cpuUsageSoftIrq)
{
    comVals_["cpuUsageSoftIrq"] = cpuUsageSoftIrq;
}
            
void XCpuUsageImp::setCpuLatencyAvg(XNumber cpuLatencyAvg)
{
    comVals_["cpuLatencyAvg"] = cpuLatencyAvg;
}
            
void XCpuUsageImp::setCpuUsageSteal(XNumber cpuUsageSteal)
{
    comVals_["cpuUsageSteal"] = cpuUsageSteal;
}
            
void XCpuUsageImp::setCpuDemandPct(XNumber cpuDemandPct)
{
    comVals_["cpuDemandPct"] = cpuDemandPct;
}
            
void XCpuUsageImp::setCpuDemandAvg(XNumber cpuDemandAvg)
{
    comVals_["cpuDemandAvg"] = cpuDemandAvg;
}
            
void XCpuUsageImp::setCpuIdle(XNumber cpuIdle)
{
    comVals_["cpuIdle"] = cpuIdle;
}
            
void XCpuUsageImp::setCpuSwapWaitTime(XNumber cpuSwapWaitTime)
{
    comVals_["cpuSwapWaitTime"] = cpuSwapWaitTime;
}
            
void XCpuUsageImp::setCpuUsageSystem(XNumber cpuUsageSystem)
{
    comVals_["cpuUsageSystem"] = cpuUsageSystem;
}
            
void XCpuUsageImp::setCpuOverheadAvg(XNumber cpuOverheadAvg)
{
    comVals_["cpuOverheadAvg"] = cpuOverheadAvg;
}
            
void XCpuUsageImp::setCpuUsageUser(XNumber cpuUsageUser)
{
    comVals_["cpuUsageUser"] = cpuUsageUser;
}
            
void XCpuUsageImp::setCpuIdentifier(const XString& cpuIdentifier)
{
    comVals_["cpuIdentifier"] = cpuIdentifier;
}

json XCpuUsageImp::toJson()
{
    try
    {
        json field = {
            {"percentUsage", percentUsage_},
            {"cpuIdentifier", cpuIdentifier_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XCpuUsage to json object:{}.", e.what());
        return json();
    }
}
            