#include "XFaultFieldsImp.h"

const std::string XEnumFaultFieldsEventSeverityMapping[] = {
    "CRITICAL",
    "MAJOR",
    "MINOR",
    "WARNING",
    "NORMAL"
};

const std::string XEnumFaultFieldsVfStatusMapping[] = {
    "Active",
    "Idle",
    "Preparing to terminate",
    "Ready to terminate",
    "Requesting termination"
};

const std::string XEnumFaultFieldsFaultFieldsVersionMapping[] = {
    "4.0"
};

const std::string XEnumFaultFieldsEventSourceTypeMapping[] = {
    "other",
    "router",
    "switch",
    "host",
    "card",
    "port",
    "slotThreshold",
    "portThreshold",
    "virtualMachine",
    "virtualNetworkFunction"
};

XFaultFieldsImp::XFaultFieldsImp(shared_ptr<XCommonEventHeader> header,
    const XString& alarmCondition,
    const XString& specificProblem,
    XEnumFaultFieldsEventSourceType eventSourceType,
    XEnumFaultFieldsEventSeverity eventSeverity,
    XEnumFaultFieldsVfStatus vfStatus):
        header_(header),
        alarmCondition_(alarmCondition),
        eventSeverity_(eventSeverity),
        eventSourceType_(eventSourceType),
        faultFieldsVersion_(XEnumFaultFieldsFaultFieldsVersion4_0),
        specificProblem_(specificProblem),
        vfStatus_(vfStatus)
{

}

std::string XFaultFieldsImp::toString()
{
    try
    {
        auto js = toJson();
        return js.dump();
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to dump XFaultFields to json string:{}.", e.what());
        return "";
    }
}

shared_ptr<XCommonEventHeader> XFaultFieldsImp::getCommonHeader()
{
    return header_;
}

void XFaultFieldsImp::setAlarmInterfaceA(const XString& alarmInterfaceA)
{
    comVals_["alarmInterfaceA"] = alarmInterfaceA;
}
            
void XFaultFieldsImp::setEventSeverity(XEnumFaultFieldsEventSeverity eventSeverity)
{
    auto val = XEnumFaultFieldsEventSeverityMapping[eventSeverity];
    comVals_["eventSeverity"] = val;
}
            
void XFaultFieldsImp::setAlarmCondition(const XString& alarmCondition)
{
    comVals_["alarmCondition"] = alarmCondition;
}
            
void XFaultFieldsImp::setVfStatus(XEnumFaultFieldsVfStatus vfStatus)
{
    auto val = XEnumFaultFieldsVfStatusMapping[vfStatus];
    comVals_["vfStatus"] = val;
}
            
void XFaultFieldsImp::setEventCategory(const XString& eventCategory)
{
    comVals_["eventCategory"] = eventCategory;
}
            
void XFaultFieldsImp::setEventSourceType(XEnumFaultFieldsEventSourceType eventSourceType)
{
    auto val = XEnumFaultFieldsEventSourceTypeMapping[eventSourceType];
    comVals_["eventSourceType"] = val;
}
            
void XFaultFieldsImp::setSpecificProblem(const XString& specificProblem)
{
    comVals_["specificProblem"] = specificProblem;
}
            
void XFaultFieldsImp::setAlarmAdditionalInformation(const XHashMap& alarmAdditionalInformation)
{
    alarmAdditionalInformation_ = alarmAdditionalInformation;
}

json XFaultFieldsImp::toJson()
{
    try
    {
        json field = {
            {"eventSeverity", XEnumFaultFieldsEventSeverityMapping[eventSeverity_]},
            {"alarmCondition", alarmCondition_},
            {"vfStatus", XEnumFaultFieldsVfStatusMapping[vfStatus_]},
            {"eventSourceType", XEnumFaultFieldsEventSourceTypeMapping[eventSourceType_]},
            {"specificProblem", specificProblem_},
            {"faultFieldsVersion", XEnumFaultFieldsFaultFieldsVersionMapping[faultFieldsVersion_]}
        };

        //optional val
        if (!alarmAdditionalInformation_.empty())
        {
            field["alarmAdditionalInformation"] = alarmAdditionalInformation_;
        }
        field = mergeCommonValues(field, comVals_);

        json jsEvent;

        header_->setDomain(XEnumCommonEventHeaderDomainFault);
        jsEvent["event"]["commonEventHeader"] = dynamic_pointer_cast<XJsonable>(header_)->toJson();
        jsEvent["event"]["faultFields"] = field;

        return jsEvent;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XFaultFields to json object:{}.", e.what());
        return json();
    }
}
            
