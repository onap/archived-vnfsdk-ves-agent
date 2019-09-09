#include "XIpmiPowerSupplyImp.h"

XIpmiPowerSupplyImp::XIpmiPowerSupplyImp(const XString& powerSupplyIdentifier):
        powerSupplyIdentifier_(powerSupplyIdentifier)
{

}

void XIpmiPowerSupplyImp::setPowerSupplyInputPower(XNumber powerSupplyInputPower)
{
    comVals_["powerSupplyInputPower"] = powerSupplyInputPower;
}
            
void XIpmiPowerSupplyImp::setPowerSupplyCurrentOutputPercent(XNumber powerSupplyCurrentOutputPercent)
{
    comVals_["powerSupplyCurrentOutputPercent"] = powerSupplyCurrentOutputPercent;
}
            
void XIpmiPowerSupplyImp::setPowerSupplyIdentifier(const XString& powerSupplyIdentifier)
{
    comVals_["powerSupplyIdentifier"] = powerSupplyIdentifier;
}
            
void XIpmiPowerSupplyImp::setPowerSupplyTemperature(XNumber powerSupplyTemperature)
{
    comVals_["powerSupplyTemperature"] = powerSupplyTemperature;
}

json XIpmiPowerSupplyImp::toJson()
{
    try
    {
        json field = {
            {"powerSupplyIdentifier", powerSupplyIdentifier_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XIpmiPowerSupply to json object:{}.", e.what());
        return json();
    }
}
            