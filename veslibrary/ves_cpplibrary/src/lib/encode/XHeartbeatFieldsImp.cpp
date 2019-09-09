#include "XHeartbeatFieldsImp.h"

const std::string XEnumHeartbeatFieldsHeartbeatFieldsVersionMapping[] = {
    "3.0"
};

XHeartbeatFieldsImp::XHeartbeatFieldsImp(std::shared_ptr<XCommonEventHeader> header, XInteger heartbeatInterval):
    header_(header),
    heartbeatFieldsVersion_(XEnumHeartbeatFieldsHeartbeatFieldsVersion3_0),
    heartbeatInterval_(heartbeatInterval)
{

}

void XHeartbeatFieldsImp::setHeartbeatInterval(XInteger heartbeatInterval)
{
    comVals_["heartbeatInterval"] = heartbeatInterval;
}
            
void XHeartbeatFieldsImp::setAdditionalFields(const XHashMap& additionalFields)
{
    additionalFields_ = additionalFields;
}

std::shared_ptr<XCommonEventHeader> XHeartbeatFieldsImp::getCommonHeader()
{
    return header_;
}

std::string XHeartbeatFieldsImp::toString()
{
    try
    {
        auto js = toJson();
        return js.dump();
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to dump XHeartbeatFields to json string:{}.", e.what());
        return "";
    }
}

json XHeartbeatFieldsImp::toJson()
{
    try
    {
        json field = {
            {"heartbeatInterval", heartbeatInterval_},
            {"heartbeatFieldsVersion", XEnumHeartbeatFieldsHeartbeatFieldsVersionMapping[heartbeatFieldsVersion_]}
        };

        //optional val
        if (!additionalFields_.empty())
        {
            field["additionalFields"] = additionalFields_;
        }

        json jsEvent;
        header_->setDomain(XEnumCommonEventHeaderDomainHeartbeat);
        jsEvent["event"]["commonEventHeader"] = dynamic_pointer_cast<XJsonable>(header_)->toJson();
        jsEvent["event"]["heartbeatFields"] = field;

        return jsEvent;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XHeartbeatFields to json object:{}.", e.what());
        return json();
    }
}
            
