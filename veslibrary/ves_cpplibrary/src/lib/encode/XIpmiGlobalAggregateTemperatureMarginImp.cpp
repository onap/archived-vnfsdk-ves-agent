#include "XIpmiGlobalAggregateTemperatureMarginImp.h"

XIpmiGlobalAggregateTemperatureMarginImp::XIpmiGlobalAggregateTemperatureMarginImp(const XString& ipmiGlobalAggregateTemperatureMarginIdentifier,
    XNumber globalAggregateTemperatureMargin):
        ipmiGlobalAggregateTemperatureMarginIdentifier_(ipmiGlobalAggregateTemperatureMarginIdentifier),
        globalAggregateTemperatureMargin_(globalAggregateTemperatureMargin)
{

}

void XIpmiGlobalAggregateTemperatureMarginImp::setIpmiGlobalAggregateTemperatureMarginIdentifier(const XString& ipmiGlobalAggregateTemperatureMarginIdentifier)
{
    comVals_["ipmiGlobalAggregateTemperatureMarginIdentifier"] = ipmiGlobalAggregateTemperatureMarginIdentifier;
}
            
void XIpmiGlobalAggregateTemperatureMarginImp::setGlobalAggregateTemperatureMargin(XNumber globalAggregateTemperatureMargin)
{
    comVals_["globalAggregateTemperatureMargin"] = globalAggregateTemperatureMargin;
}

json XIpmiGlobalAggregateTemperatureMarginImp::toJson()
{
    try
    {
        json field = {
            {"ipmiGlobalAggregateTemperatureMarginIdentifier", ipmiGlobalAggregateTemperatureMarginIdentifier_},
            {"globalAggregateTemperatureMargin", globalAggregateTemperatureMargin_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XIpmiGlobalAggregateTemperatureMargin to json object:{}.", e.what());
        return json();
    }
}
            