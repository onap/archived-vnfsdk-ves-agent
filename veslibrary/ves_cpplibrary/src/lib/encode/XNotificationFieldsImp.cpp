#include "XNotificationFieldsImp.h"

const std::string XEnumNotificationFieldsNotificationFieldsVersionMapping[] = {
    "2.0"
};

XNotificationFieldsImp::XNotificationFieldsImp(std::shared_ptr<XCommonEventHeader> header,
    const XString& changeIdentifier,
    const XString& changeType
    ):
        header_(header),
        changeIdentifier_(changeIdentifier),
        changeType_(changeType),
        notificationFieldsVersion_(XEnumNotificationFieldsNotificationFieldsVersion2_0)
{

}

std::string XNotificationFieldsImp::toString()
{
    try
    {
        auto js = toJson();
        return js.dump();
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to dump XNotificationFields to json string:{}.", e.what());
        return "";
    }
}

void XNotificationFieldsImp::setNewState(const XString& newState)
{
    comVals_["newState"] = newState;
}
            
void XNotificationFieldsImp::setChangeType(const XString& changeType)
{
    comVals_["changeType"] = changeType;
}
            
void XNotificationFieldsImp::setArrayOfNamedHashMap(const XArrayOfNamedHashMap& arrayOfNamedHashMap)
{
    arrayOfNamedHashMap_ = arrayOfNamedHashMap;
}
            
void XNotificationFieldsImp::setChangeContact(const XString& changeContact)
{
    comVals_["changeContact"] = changeContact;
}
            
void XNotificationFieldsImp::setChangeIdentifier(const XString& changeIdentifier)
{
    comVals_["changeIdentifier"] = changeIdentifier;
}
            
void XNotificationFieldsImp::setAdditionalFields(const XHashMap& additionalFields)
{
    additionalFields_ = additionalFields;
}
            
void XNotificationFieldsImp::setOldState(const XString& oldState)
{
    comVals_["oldState"] = oldState;
}
            
void XNotificationFieldsImp::setStateInterface(const XString& stateInterface)
{
    comVals_["stateInterface"] = stateInterface;
}

json XNotificationFieldsImp::toJson()
{
    try
    {
        json field = {
            {"notificationFieldsVersion", XEnumNotificationFieldsNotificationFieldsVersionMapping[notificationFieldsVersion_]},
            {"changeType", changeType_},
            {"changeIdentifier", changeIdentifier_}
        };

        //optional val
        if (!arrayOfNamedHashMap_.empty())
        {
            field["arrayOfNamedHashMap"] = fromArray(arrayOfNamedHashMap_);
        }

        if (!additionalFields_.empty())
        {
            field["additionalFields"] = additionalFields_;
        }

        field = mergeCommonValues(field, comVals_);

        json jsEvent;
        header_->setDomain(XEnumCommonEventHeaderDomainNotification);
        jsEvent["event"]["commonEventHeader"] = dynamic_pointer_cast<XJsonable>(header_)->toJson();
        jsEvent["event"]["notificationFields"] = field;

        return jsEvent;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XNotificationFields to json object:{}.", e.what());
        return json();
    }
}

std::shared_ptr<XCommonEventHeader> XNotificationFieldsImp::getCommonHeader()
{
    return header_;
}
            