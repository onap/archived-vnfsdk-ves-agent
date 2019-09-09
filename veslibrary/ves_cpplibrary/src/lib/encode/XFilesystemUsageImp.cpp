#include "XFilesystemUsageImp.h"

XFilesystemUsageImp::XFilesystemUsageImp(const XString& filesystemName,
    XNumber blockConfigured,
    XNumber blockIops,
    XNumber blockUsed,
    XNumber ephemeralConfigured,
    XNumber ephemeralIops,
    XNumber ephemeralUsed):
        blockConfigured_(blockConfigured),
        blockIops_(blockIops),
        blockUsed_(blockUsed),
        ephemeralConfigured_(ephemeralConfigured),
        ephemeralIops_(ephemeralIops),
        ephemeralUsed_(ephemeralUsed),
        filesystemName_(filesystemName)
{

}

void XFilesystemUsageImp::setBlockConfigured(XNumber blockConfigured)
{
    comVals_["blockConfigured"] = blockConfigured;
}
            
void XFilesystemUsageImp::setBlockUsed(XNumber blockUsed)
{
    comVals_["blockUsed"] = blockUsed;
}
            
void XFilesystemUsageImp::setEphemeralConfigured(XNumber ephemeralConfigured)
{
    comVals_["ephemeralConfigured"] = ephemeralConfigured;
}
            
void XFilesystemUsageImp::setEphemeralIops(XNumber ephemeralIops)
{
    comVals_["ephemeralIops"] = ephemeralIops;
}
            
void XFilesystemUsageImp::setFilesystemName(const XString& filesystemName)
{
    comVals_["filesystemName"] = filesystemName;
}
            
void XFilesystemUsageImp::setBlockIops(XNumber blockIops)
{
    comVals_["blockIops"] = blockIops;
}
            
void XFilesystemUsageImp::setEphemeralUsed(XNumber ephemeralUsed)
{
    comVals_["ephemeralUsed"] = ephemeralUsed;
}

json XFilesystemUsageImp::toJson()
{
    try
    {
        json field = {
            {"blockConfigured", blockConfigured_},
            {"blockUsed", blockUsed_},
            {"ephemeralConfigured", ephemeralConfigured_},
            {"ephemeralIops", ephemeralIops_},
            {"filesystemName", filesystemName_},
            {"blockIops", blockIops_},
            {"ephemeralUsed", ephemeralUsed_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XFilesystemUsage to json object:{}.", e.what());
        return json();
    }
}
            