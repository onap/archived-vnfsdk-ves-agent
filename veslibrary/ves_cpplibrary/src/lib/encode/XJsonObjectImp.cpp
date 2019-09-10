#include "XJsonObjectImp.h"

XJsonObjectImp::XJsonObjectImp(const XString& objectName,
    const XArrayOfXJsonObjectInstance& objectInstances
    ):
        objectInstances_(objectInstances),
        objectName_(objectName)
{

}

void XJsonObjectImp::setObjectSchema(const XString& objectSchema)
{
    comVals_["objectSchema"] = objectSchema;
}
            
void XJsonObjectImp::setObjectName(const XString& objectName)
{
    comVals_["objectName"] = objectName;
}
            
void XJsonObjectImp::setNfSubscriptionId(const XString& nfSubscriptionId)
{
    comVals_["nfSubscriptionId"] = nfSubscriptionId;
}
            
void XJsonObjectImp::setObjectInstances(const XArrayOfXJsonObjectInstance& objectInstances)
{
    objectInstances_ = objectInstances;
}
            
void XJsonObjectImp::setNfSubscribedObjectName(const XString& nfSubscribedObjectName)
{
    comVals_["nfSubscribedObjectName"] = nfSubscribedObjectName;
}
            
void XJsonObjectImp::setObjectSchemaUrl(const XString& objectSchemaUrl)
{
    comVals_["objectSchemaUrl"] = objectSchemaUrl;
}

json XJsonObjectImp::toJson()
{
    try
    {
        json field = {
            {"objectName", objectName_}
        };

        field["objectInstances"] = fromArray(objectInstances_);

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XJsonObject to json object:{}.", e.what());
        return json();
    }
}
            