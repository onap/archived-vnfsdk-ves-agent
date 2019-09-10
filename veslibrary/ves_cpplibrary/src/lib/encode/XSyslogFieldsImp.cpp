#include "XSyslogFieldsImp.h"

const std::string XEnumSyslogFieldsEventSourceTypeMapping[] = {
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

const std::string XEnumSyslogFieldsSyslogSevMapping[] = {
    "Alert",
    "Critical",
    "Debug",
    "Emergency",
    "Error",
    "Info",
    "Notice",
    "Warning"
};

const std::string XEnumSyslogFieldsSyslogFieldsVersionMapping[] = {
    "4.0"
};

XSyslogFieldsImp::XSyslogFieldsImp(std::shared_ptr<XCommonEventHeader> header,
    XEnumSyslogFieldsEventSourceType eventSourceType,
    const XString& syslogTag,
    const XString& syslogMsg
    ):
        header_(header),
        eventSourceType_(eventSourceType),
        syslogFieldsVersion_(XEnumSyslogFieldsSyslogFieldsVersion4_0),
        syslogMsg_(syslogMsg),
        syslogTag_(syslogTag)
{

}

std::string XSyslogFieldsImp::toString()
{
    try
    {
        auto js = toJson();
        return js.dump();
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to dump XSyslogFields to json string:{}.", e.what());
        return "";
    }
}

void XSyslogFieldsImp::setSyslogProcId(XNumber syslogProcId)
{
    comVals_["syslogProcId"] = syslogProcId;
}
            
void XSyslogFieldsImp::setSyslogFacility(XInteger syslogFacility)
{
    comVals_["syslogFacility"] = syslogFacility;
}
            
void XSyslogFieldsImp::setSyslogPri(XInteger syslogPri)
{
    comVals_["syslogPri"] = syslogPri;
}
            
void XSyslogFieldsImp::setEventSourceType(XEnumSyslogFieldsEventSourceType eventSourceType)
{
    auto val = XEnumSyslogFieldsEventSourceTypeMapping[eventSourceType];
    comVals_["eventSourceType"] = val;
}
            
void XSyslogFieldsImp::setSyslogMsgHost(const XString& syslogMsgHost)
{
    comVals_["syslogMsgHost"] = syslogMsgHost;
}
            
void XSyslogFieldsImp::setSyslogSev(XEnumSyslogFieldsSyslogSev syslogSev)
{
    auto val = XEnumSyslogFieldsSyslogSevMapping[syslogSev];
    comVals_["syslogSev"] = val;
}
            
void XSyslogFieldsImp::setSyslogSData(const XString& syslogSData)
{
    comVals_["syslogSData"] = syslogSData;
}
            
void XSyslogFieldsImp::setSyslogMsg(const XString& syslogMsg)
{
    comVals_["syslogMsg"] = syslogMsg;
}
            
void XSyslogFieldsImp::setSyslogProc(const XString& syslogProc)
{
    comVals_["syslogProc"] = syslogProc;
}
            
void XSyslogFieldsImp::setEventSourceHost(const XString& eventSourceHost)
{
    comVals_["eventSourceHost"] = eventSourceHost;
}
            
void XSyslogFieldsImp::setSyslogTs(const XString& syslogTs)
{
    comVals_["syslogTs"] = syslogTs;
}
            
void XSyslogFieldsImp::setSyslogTag(const XString& syslogTag)
{
    comVals_["syslogTag"] = syslogTag;
}
            
void XSyslogFieldsImp::setSyslogVer(XNumber syslogVer)
{
    comVals_["syslogVer"] = syslogVer;
}
            
void XSyslogFieldsImp::setAdditionalFields(const XHashMap& additionalFields)
{
    additionalFields_ = additionalFields;
}
            
void XSyslogFieldsImp::setSyslogSdId(const XString& syslogSdId)
{
    comVals_["syslogSdId"] = syslogSdId;
}

json XSyslogFieldsImp::toJson()
{
    try
    {
        json field = {
            { "eventSourceType", XEnumSyslogFieldsEventSourceTypeMapping[eventSourceType_] },
            { "syslogMsg", syslogMsg_ },
            { "syslogFieldsVersion", XEnumSyslogFieldsSyslogFieldsVersionMapping[syslogFieldsVersion_] },
            { "syslogTag", syslogTag_ }
        };

        //optional val
        if (!additionalFields_.empty())
        {
            field["additionalFields"] = additionalFields_;
        }

        field = mergeCommonValues(field, comVals_);

        json jsEvent;
        header_->setDomain(XEnumCommonEventHeaderDomainSyslog);
        jsEvent["event"]["commonEventHeader"] = dynamic_pointer_cast<XJsonable>(header_)->toJson();
        jsEvent["event"]["syslogFields"] = field;

        return jsEvent;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XSyslogFields to json object:{}.", e.what());
        return json();
    }
}

std::shared_ptr<XCommonEventHeader> XSyslogFieldsImp::getCommonHeader()
{
    return header_;
}
            