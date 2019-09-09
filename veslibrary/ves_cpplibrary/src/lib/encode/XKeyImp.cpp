#include "XKeyImp.h"

XKeyImp::XKeyImp(const XString& keyName):
        keyName_(keyName)
{

}

void XKeyImp::setKeyValue(const XString& keyValue)
{
    comVals_["keyValue"] = keyValue;
}
            
void XKeyImp::setKeyOrder(XInteger keyOrder)
{
    comVals_["keyOrder"] = keyOrder;
}
            
void XKeyImp::setKeyName(const XString& keyName)
{
    comVals_["keyName"] = keyName;
}

json XKeyImp::toJson()
{
    try
    {
        json field = {
            {"keyName", keyName_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XKey to json object:{}.", e.what());
        return json();
    }
}
            