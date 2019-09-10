#include "XThresholdCrossingAlertFieldsImp.h"

const std::string XEnumThresholdCrossingAlertFieldsThresholdCrossingFieldsVersionMapping[] = {
    "4.0"
};

const std::string XEnumThresholdCrossingAlertFieldsAlertTypeMapping[] = {
    "CARD-ANOMALY",
    "ELEMENT-ANOMALY",
    "INTERFACE-ANOMALY",
    "SERVICE-ANOMALY"
};

const std::string XEnumThresholdCrossingAlertFieldsEventSeverityMapping[] = {
    "CRITICAL",
    "MAJOR",
    "MINOR",
    "WARNING",
    "NORMAL"
};

const std::string XEnumThresholdCrossingAlertFieldsAlertActionMapping[] = {
    "CLEAR",
    "CONT",
    "SET"
};

XThresholdCrossingAlertFieldsImp::XThresholdCrossingAlertFieldsImp(std::shared_ptr<XCommonEventHeader> header,
                XEnumThresholdCrossingAlertFieldsAlertAction alertAction,
                XEnumThresholdCrossingAlertFieldsAlertType alertType,
                XEnumThresholdCrossingAlertFieldsEventSeverity eventSeverity,
                const XString& alertDescription,
                const XString& collectionTimestamp,
                const XString& eventStartTimestamp,
                const XArrayOfXCounter& additionalParameters
                ):
        header_(header),
        additionalParameters_(additionalParameters),
        alertAction_(alertAction),
        alertDescription_(alertDescription),
        alertType_(alertType),
        collectionTimestamp_(collectionTimestamp),
        eventSeverity_(eventSeverity),
        eventStartTimestamp_(eventStartTimestamp),
        thresholdCrossingFieldsVersion_(XEnumThresholdCrossingAlertFieldsThresholdCrossingFieldsVersion4_0)
{

}

std::string XThresholdCrossingAlertFieldsImp::toString()
{
    try
    {
        auto js = toJson();
        return js.dump();
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to dump XThresholdCrossingAlertFields to json string:{}.", e.what());
        return "";
    }
}

void XThresholdCrossingAlertFieldsImp::setAlertDescription(const XString& alertDescription)
{
    comVals_["alertDescription"] = alertDescription;
}
            
void XThresholdCrossingAlertFieldsImp::setAlertType(XEnumThresholdCrossingAlertFieldsAlertType alertType)
{
    auto val = XEnumThresholdCrossingAlertFieldsAlertTypeMapping[alertType];
    comVals_["alertType"] = val;
}
            
void XThresholdCrossingAlertFieldsImp::setInterfaceName(const XString& interfaceName)
{
    comVals_["interfaceName"] = interfaceName;
}
            
void XThresholdCrossingAlertFieldsImp::setCollectionTimestamp(const XString& collectionTimestamp)
{
    comVals_["collectionTimestamp"] = collectionTimestamp;
}
            
void XThresholdCrossingAlertFieldsImp::setEventSeverity(XEnumThresholdCrossingAlertFieldsEventSeverity eventSeverity)
{
    auto val = XEnumThresholdCrossingAlertFieldsEventSeverityMapping[eventSeverity];
    comVals_["eventSeverity"] = val;
}
            
void XThresholdCrossingAlertFieldsImp::setPossibleRootCause(const XString& possibleRootCause)
{
    comVals_["possibleRootCause"] = possibleRootCause;
}
            
void XThresholdCrossingAlertFieldsImp::setAssociatedAlertIdList(const XArrayOfString& associatedAlertIdList)
{
    associatedAlertIdList_ = associatedAlertIdList;
}
            
void XThresholdCrossingAlertFieldsImp::setAlertValue(const XString& alertValue)
{
    comVals_["alertValue"] = alertValue;
}
            
void XThresholdCrossingAlertFieldsImp::setDataCollector(const XString& dataCollector)
{
    comVals_["dataCollector"] = dataCollector;
}
            
void XThresholdCrossingAlertFieldsImp::setAdditionalParameters(const XArrayOfXCounter& additionalParameters)
{
    additionalParameters_ = additionalParameters;
}
            
void XThresholdCrossingAlertFieldsImp::setAlertAction(XEnumThresholdCrossingAlertFieldsAlertAction alertAction)
{
    auto val = XEnumThresholdCrossingAlertFieldsAlertActionMapping[alertAction];
    comVals_["alertAction"] = val;
}
            
void XThresholdCrossingAlertFieldsImp::setNetworkService(const XString& networkService)
{
    comVals_["networkService"] = networkService;
}
            
void XThresholdCrossingAlertFieldsImp::setElementType(const XString& elementType)
{
    comVals_["elementType"] = elementType;
}
            
void XThresholdCrossingAlertFieldsImp::setAdditionalFields(const XHashMap& additionalFields)
{
    additionalFields_ = additionalFields;
}
            
void XThresholdCrossingAlertFieldsImp::setEventStartTimestamp(const XString& eventStartTimestamp)
{
    comVals_["eventStartTimestamp"] = eventStartTimestamp;
}

json XThresholdCrossingAlertFieldsImp::toJson()
{
    try
    {
        json field = {
            {"thresholdCrossingFieldsVersion", XEnumThresholdCrossingAlertFieldsThresholdCrossingFieldsVersionMapping[thresholdCrossingFieldsVersion_]},
            {"alertDescription", alertDescription_},
            {"alertType", XEnumThresholdCrossingAlertFieldsAlertTypeMapping[alertType_]},
            {"collectionTimestamp", collectionTimestamp_},
            {"eventSeverity", XEnumThresholdCrossingAlertFieldsEventSeverityMapping[eventSeverity_]},
            {"additionalParameters", fromArray(additionalParameters_)},
            {"alertAction", XEnumThresholdCrossingAlertFieldsAlertActionMapping[alertAction_]},
            {"eventStartTimestamp", eventStartTimestamp_}
        };

        //optional val
        if (!associatedAlertIdList_.empty())
        {
            field["associatedAlertIdList"] = associatedAlertIdList_;
        }

        if (!additionalFields_.empty())
        {
            field["additionalFields"] = additionalFields_;
        }

        field = mergeCommonValues(field, comVals_);

        json jsEvent;
        header_->setDomain(XEnumCommonEventHeaderDomainThresholdCrossingAlert);
        jsEvent["event"]["commonEventHeader"] = dynamic_pointer_cast<XJsonable>(header_)->toJson();
        jsEvent["event"]["thresholdCrossingAlertFields"] = field;

        return jsEvent;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XThresholdCrossingAlertFields to json object:{}.", e.what());
        return json();
    }
}

std::shared_ptr<XCommonEventHeader> XThresholdCrossingAlertFieldsImp::getCommonHeader()
{
    return header_;
}
            