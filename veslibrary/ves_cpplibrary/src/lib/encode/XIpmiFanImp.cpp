#include "XIpmiFanImp.h"

XIpmiFanImp::XIpmiFanImp(const XString& fanIdentifier):
        fanIdentifier_(fanIdentifier)
{

}

void XIpmiFanImp::setFanSpeed(XNumber fanSpeed)
{
    comVals_["fanSpeed"] = fanSpeed;
}
            
void XIpmiFanImp::setFanIdentifier(const XString& fanIdentifier)
{
    comVals_["fanIdentifier"] = fanIdentifier;
}

json XIpmiFanImp::toJson()
{
    try
    {
        json field = {
            {"fanIdentifier", fanIdentifier_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XIpmiFan to json object:{}.", e.what());
        return json();
    }
}
            