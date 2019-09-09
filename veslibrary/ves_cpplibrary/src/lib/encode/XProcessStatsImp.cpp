#include "XProcessStatsImp.h"

XProcessStatsImp::XProcessStatsImp(const XString& processIdentifier):
        processIdentifier_(processIdentifier)
{

}

void XProcessStatsImp::setForkRate(XNumber forkRate)
{
    comVals_["forkRate"] = forkRate;
}
            
void XProcessStatsImp::setPsStateStopped(XNumber psStateStopped)
{
    comVals_["psStateStopped"] = psStateStopped;
}
            
void XProcessStatsImp::setPsStatePaging(XNumber psStatePaging)
{
    comVals_["psStatePaging"] = psStatePaging;
}
            
void XProcessStatsImp::setPsStateSleeping(XNumber psStateSleeping)
{
    comVals_["psStateSleeping"] = psStateSleeping;
}
            
void XProcessStatsImp::setProcessIdentifier(const XString& processIdentifier)
{
    comVals_["processIdentifier"] = processIdentifier;
}
            
void XProcessStatsImp::setPsStateBlocked(XNumber psStateBlocked)
{
    comVals_["psStateBlocked"] = psStateBlocked;
}
            
void XProcessStatsImp::setPsStateZombie(XNumber psStateZombie)
{
    comVals_["psStateZombie"] = psStateZombie;
}
            
void XProcessStatsImp::setPsStateRunning(XNumber psStateRunning)
{
    comVals_["psStateRunning"] = psStateRunning;
}

json XProcessStatsImp::toJson()
{
    try
    {
        json field = {
            {"processIdentifier", processIdentifier_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XProcessStats to json object:{}.", e.what());
        return json();
    }
}
            