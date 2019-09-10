#include "XIpmiBatteryImp.h"

XIpmiBatteryImp::XIpmiBatteryImp(const XString& batteryIdentifier):
        batteryIdentifier_(batteryIdentifier)
{

}

void XIpmiBatteryImp::setBatteryType(const XString& batteryType)
{
    comVals_["batteryType"] = batteryType;
}
            
void XIpmiBatteryImp::setBatteryIdentifier(const XString& batteryIdentifier)
{
    comVals_["batteryIdentifier"] = batteryIdentifier;
}
            
void XIpmiBatteryImp::setBatteryVoltageLevel(XNumber batteryVoltageLevel)
{
    comVals_["batteryVoltageLevel"] = batteryVoltageLevel;
}

json XIpmiBatteryImp::toJson()
{
    try
    {
        json field = {
            {"batteryIdentifier", batteryIdentifier_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XIpmiBattery to json object:{}.", e.what());
        return json();
    }
}
            