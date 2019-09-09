#include "XStateChangeFieldsImp.h"

const std::string XEnumStateChangeFieldsStateChangeFieldsVersionMapping[] = {
    "4.0"
};

const std::string XEnumStateChangeFieldsStateMapping[] = {
    "inService",
    "maintenance",
    "outOfService"
};

XStateChangeFieldsImp::XStateChangeFieldsImp(std::shared_ptr<XCommonEventHeader> header,
    XEnumStateChangeFieldsState newState,
    XEnumStateChangeFieldsState oldState,
    const XString& stateInterface):
        header_(header),
        newState_(newState),
        oldState_(oldState),
        stateChangeFieldsVersion_(XEnumStateChangeFieldsStateChangeFieldsVersion4_0),
        stateInterface_(stateInterface)
{

}

std::string XStateChangeFieldsImp::toString()
{
    try
    {
        auto js = toJson();
        return js.dump();
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to dump XStateChangeFields to json string:{}.", e.what());
        return "";
    }
}

void XStateChangeFieldsImp::setNewState(XEnumStateChangeFieldsState newState)
{
    auto val = XEnumStateChangeFieldsStateMapping[newState];
    comVals_["newState"] = val;
}
            
void XStateChangeFieldsImp::setOldState(XEnumStateChangeFieldsState oldState)
{
    auto val = XEnumStateChangeFieldsStateMapping[oldState];
    comVals_["oldState"] = val;
}
            
void XStateChangeFieldsImp::setAdditionalFields(const XHashMap& additionalFields)
{
    additionalFields_ = additionalFields;
}
            
void XStateChangeFieldsImp::setStateInterface(const XString& stateInterface)
{
    comVals_["stateInterface"] = stateInterface;
}

json XStateChangeFieldsImp::toJson()
{
    try
    {
        json field = {
            {"stateChangeFieldsVersion", XEnumStateChangeFieldsStateChangeFieldsVersionMapping[stateChangeFieldsVersion_]},
            {"newState", XEnumStateChangeFieldsStateMapping[newState_]},
            {"oldState", XEnumStateChangeFieldsStateMapping[oldState_]},
            {"stateInterface", stateInterface_}
        };

        //optional val
        if (!additionalFields_.empty())
        {
            field["additionalFields"] = additionalFields_;
        }

        field = mergeCommonValues(field, comVals_);

        json jsEvent;
        header_->setDomain(XEnumCommonEventHeaderDomainStateChange);
        jsEvent["event"]["commonEventHeader"] = dynamic_pointer_cast<XJsonable>(header_)->toJson();
        jsEvent["event"]["stateChangeFields"] = field;

        return jsEvent;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XStateChangeFields to json object:{}.", e.what());
        return json();
    }
}

std::shared_ptr<XCommonEventHeader> XStateChangeFieldsImp::getCommonHeader()
{
    return header_;
}
            