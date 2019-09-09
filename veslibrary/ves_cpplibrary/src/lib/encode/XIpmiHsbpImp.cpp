#include "XIpmiHsbpImp.h"

XIpmiHsbpImp::XIpmiHsbpImp(const XString& hsbpIdentifier):
        hsbpIdentifier_(hsbpIdentifier)
{

}

void XIpmiHsbpImp::setHsbpTemperature(XNumber hsbpTemperature)
{
    comVals_["hsbpTemperature"] = hsbpTemperature;
}
            
void XIpmiHsbpImp::setHsbpIdentifier(const XString& hsbpIdentifier)
{
    comVals_["hsbpIdentifier"] = hsbpIdentifier;
}

json XIpmiHsbpImp::toJson()
{
    try
    {
        json field = {
            {"hsbpIdentifier", hsbpIdentifier_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XIpmiHsbp to json object:{}.", e.what());
        return json();
    }
}
            