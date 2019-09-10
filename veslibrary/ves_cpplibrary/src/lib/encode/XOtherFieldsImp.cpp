#include "XOtherFieldsImp.h"

const std::string XEnumOtherFieldsOtherFieldsVersionMapping[] = {
    "3.0"
};

XOtherFieldsImp::XOtherFieldsImp(std::shared_ptr<XCommonEventHeader> header):
        header_(header),
        otherFieldsVersion_(XEnumOtherFieldsOtherFieldsVersion3_0)
{

}

std::string XOtherFieldsImp::toString()
{
    try
    {
        auto js = toJson();
        return js.dump();
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to dump XOtherFields to json string:{}.", e.what());
        return "";
    }
}

void XOtherFieldsImp::setJsonObjects(const XArrayOfJsonObject& jsonObjects)
{
    jsonObjects_ = jsonObjects;
}
            
void XOtherFieldsImp::setArrayOfNamedHashMap(const XArrayOfNamedHashMap& arrayOfNamedHashMap)
{
    arrayOfNamedHashMap_ = arrayOfNamedHashMap;
}
            
void XOtherFieldsImp::setHashMap(const XHashMap& hashMap)
{
    hashMap_ = hashMap;
}

json XOtherFieldsImp::toJson()
{
    try
    {
        json field = {
            {"otherFieldsVersion", XEnumOtherFieldsOtherFieldsVersionMapping[otherFieldsVersion_]}
        };

        //optional val
        if (!jsonObjects_.empty())
        {
            field["jsonObjects"] = fromArray(jsonObjects_);
        }

        if (!arrayOfNamedHashMap_.empty())
        {
            field["arrayOfNamedHashMap"] = fromArray(arrayOfNamedHashMap_);
        }

        if (!hashMap_.empty())
        {
            field["hashMap"] = hashMap_;
        }

        json jsEvent;
        header_->setDomain(XEnumCommonEventHeaderDomainOther);
        jsEvent["event"]["commonEventHeader"] = dynamic_pointer_cast<XJsonable>(header_)->toJson();
        jsEvent["event"]["otherFields"] = field;

        return jsEvent;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XOtherFields to json object:{}.", e.what());
        return json();
    }
}

std::shared_ptr<XCommonEventHeader> XOtherFieldsImp::getCommonHeader()
{
    return header_;
}
            