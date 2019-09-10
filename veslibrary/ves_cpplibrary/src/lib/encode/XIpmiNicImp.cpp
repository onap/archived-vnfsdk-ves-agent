#include "XIpmiNicImp.h"

XIpmiNicImp::XIpmiNicImp(const XString& nicIdentifier):
        nicIdentifier_(nicIdentifier)
{

}

void XIpmiNicImp::setNicIdentifier(const XString& nicIdentifier)
{
    comVals_["nicIdentifier"] = nicIdentifier;
}
            
void XIpmiNicImp::setNicTemperature(XNumber nicTemperature)
{
    comVals_["nicTemperature"] = nicTemperature;
}

json XIpmiNicImp::toJson()
{
    try
    {
        json field = {
            {"nicIdentifier", nicIdentifier_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XIpmiNic to json object:{}.", e.what());
        return json();
    }
}
            