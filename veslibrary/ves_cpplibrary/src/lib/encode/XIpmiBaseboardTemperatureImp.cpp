#include "XIpmiBaseboardTemperatureImp.h"

XIpmiBaseboardTemperatureImp::XIpmiBaseboardTemperatureImp(const XString& baseboardTemperatureIdentifier):
        baseboardTemperatureIdentifier_(baseboardTemperatureIdentifier)
{

}

void XIpmiBaseboardTemperatureImp::setBaseboardTemperature(XNumber baseboardTemperature)
{
    comVals_["baseboardTemperature"] = baseboardTemperature;
}
            
void XIpmiBaseboardTemperatureImp::setBaseboardTemperatureIdentifier(const XString& baseboardTemperatureIdentifier)
{
    comVals_["baseboardTemperatureIdentifier"] = baseboardTemperatureIdentifier;
}

json XIpmiBaseboardTemperatureImp::toJson()
{
    try
    {
        json field = {
            {"baseboardTemperatureIdentifier", baseboardTemperatureIdentifier_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XIpmiBaseboardTemperature to json object:{}.", e.what());
        return json();
    }
}
            