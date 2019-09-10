#include "XJsonObjectInstanceImp.h"

XJsonObjectInstanceImp::XJsonObjectInstanceImp():XJsonObjectInstance(nullptr)
{
}

void XJsonObjectInstanceImp::setJsonObject(const XJsonObject& jsonObject)
{
    jsonObject_ = jsonObject.imp_;
}
            
void XJsonObjectInstanceImp::setObjectInstance(const XString& objectInstance)
{
    objectInstance_ = objectInstance;
}
            
void XJsonObjectInstanceImp::setObjectInstanceEpochMicrosec(XNumber objectInstanceEpochMicrosec)
{
    comVals_["objectInstanceEpochMicrosec"] = objectInstanceEpochMicrosec;
}
            
void XJsonObjectInstanceImp::setObjectKeys(const XArrayOfXKey& objectKeys)
{
    objectKeys_ = objectKeys;
}

json XJsonObjectInstanceImp::toJson()
{
    try
    {
        json field;

        //optional val
        if (jsonObject_)
        {
            auto jsobj = dynamic_pointer_cast<XJsonable>(jsonObject_);
            if (!jsobj->toJson().empty())
            {
                field["jsonObject"] = jsobj->toJson();
            }
        }

        if (!objectKeys_.empty())
        {
            field["objectKeys"] = fromArray(objectKeys_);
        }

        if (!objectInstance_.empty())
        {
            field["objectInstance"] = json::parse(objectInstance_);
        }

        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XJsonObjectInstance to json object:{}.", e.what());
        return json();
    }
}
            