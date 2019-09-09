#include "XNamedHashMapImp.h"

XNamedHashMapImp::XNamedHashMapImp(const XString& name,
    const XHashMap& hashMap):
        name_(name),
        hashMap_(hashMap)
{

}

void XNamedHashMapImp::setName(const XString& name)
{
    comVals_["name"] = name;
}
            
void XNamedHashMapImp::setHashMap(const XHashMap& hashMap)
{
    hashMap_ = hashMap;
}

json XNamedHashMapImp::toJson()
{
    try
    {
        json field = {
            {"name", name_},
            {"hashMap", hashMap_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XNamedHashMap to json object:{}.", e.what());
        return json();
    }
}
            