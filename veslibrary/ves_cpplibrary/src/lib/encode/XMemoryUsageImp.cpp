#include "XMemoryUsageImp.h"

XMemoryUsageImp::XMemoryUsageImp(const XString& vmIdentifier,
    XNumber memoryFree,
    XNumber memoryUsed
    ):
        memoryFree_(memoryFree),
        memoryUsed_(memoryUsed),
        vmIdentifier_(vmIdentifier)
{

}

void XMemoryUsageImp::setMemorySwapInAvg(XNumber memorySwapInAvg)
{
    comVals_["memorySwapInAvg"] = memorySwapInAvg;
}
            
void XMemoryUsageImp::setMemorySwapUsedAvg(XNumber memorySwapUsedAvg)
{
    comVals_["memorySwapUsedAvg"] = memorySwapUsedAvg;
}
            
void XMemoryUsageImp::setMemorySlabRecl(XNumber memorySlabRecl)
{
    comVals_["memorySlabRecl"] = memorySlabRecl;
}
            
void XMemoryUsageImp::setMemorySwapInRateAvg(XNumber memorySwapInRateAvg)
{
    comVals_["memorySwapInRateAvg"] = memorySwapInRateAvg;
}
            
void XMemoryUsageImp::setMemoryDemand(XNumber memoryDemand)
{
    comVals_["memoryDemand"] = memoryDemand;
}
            
void XMemoryUsageImp::setMemoryConfigured(XNumber memoryConfigured)
{
    comVals_["memoryConfigured"] = memoryConfigured;
}
            
void XMemoryUsageImp::setMemorySharedAvg(XNumber memorySharedAvg)
{
    comVals_["memorySharedAvg"] = memorySharedAvg;
}
            
void XMemoryUsageImp::setVmIdentifier(const XString& vmIdentifier)
{
    comVals_["vmIdentifier"] = vmIdentifier;
}
            
void XMemoryUsageImp::setMemoryLatencyAvg(XNumber memoryLatencyAvg)
{
    comVals_["memoryLatencyAvg"] = memoryLatencyAvg;
}
            
void XMemoryUsageImp::setMemorySwapOutAvg(XNumber memorySwapOutAvg)
{
    comVals_["memorySwapOutAvg"] = memorySwapOutAvg;
}
            
void XMemoryUsageImp::setMemorySwapOutRateAvg(XNumber memorySwapOutRateAvg)
{
    comVals_["memorySwapOutRateAvg"] = memorySwapOutRateAvg;
}
            
void XMemoryUsageImp::setMemoryFree(XNumber memoryFree)
{
    comVals_["memoryFree"] = memoryFree;
}
            
void XMemoryUsageImp::setMemorySlabUnrecl(XNumber memorySlabUnrecl)
{
    comVals_["memorySlabUnrecl"] = memorySlabUnrecl;
}
            
void XMemoryUsageImp::setMemoryCached(XNumber memoryCached)
{
    comVals_["memoryCached"] = memoryCached;
}
            
void XMemoryUsageImp::setMemoryUsed(XNumber memoryUsed)
{
    comVals_["memoryUsed"] = memoryUsed;
}
            
void XMemoryUsageImp::setMemoryBuffered(XNumber memoryBuffered)
{
    comVals_["memoryBuffered"] = memoryBuffered;
}
            
void XMemoryUsageImp::setPercentMemoryUsage(XNumber percentMemoryUsage)
{
    comVals_["percentMemoryUsage"] = percentMemoryUsage;
}

json XMemoryUsageImp::toJson()
{
    try
    {
        json field = {
            {"vmIdentifier", vmIdentifier_},
            {"memoryFree", memoryFree_},
            {"memoryUsed", memoryUsed_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XMemoryUsage to json object:{}.", e.what());
        return json();
    }
}
            