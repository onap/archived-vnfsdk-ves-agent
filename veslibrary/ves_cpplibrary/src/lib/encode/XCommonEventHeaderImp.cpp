#include <sys/time.h>
#include "XCommonEventHeaderImp.h"

const std::string XEnumCommonEventHeaderVersionMapping[] = {
    "4.0.1"
};

const std::string XEnumCommonEventHeaderVesEventListenerVersionMapping[] = {
    "7.0.1"
};

const std::string XEnumCommonEventHeaderDomainMapping[] = {
    "fault",
    "heartbeat",
    "measurement",
    "mobileFlow",
    "notification",
    "other",
    "pnfRegistration",
    "sipSignaling",
    "stateChange",
    "syslog",
    "thresholdCrossingAlert",
    "voiceQuality"
};

const std::string XEnumCommonEventHeaderPriorityMapping[] = {
    "High",
    "Medium",
    "Normal",
    "Low"
};

XCommonEventHeaderImp::XCommonEventHeaderImp(
    const XString& eventName,
    const XString& eventId,
    const XString& sourceName,
    const XString& reportingEntityName,
    XEnumCommonEventHeaderPriority priority,
    XInteger sequence):
        domain_(XEnumCommonEventHeaderDomainOther),
        eventName_(eventName),
        eventId_(eventId),
        sourceName_(sourceName),
        reportingEntityName_(reportingEntityName),
        priority_(priority),
        sequence_(sequence),
        version_(XEnumCommonEventHeaderVersion4_0_1),
        vesEventListenerVersion_(XEnumCommonEventHeaderVesEventListenerVersion7_0_1)
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);

    startEpochMicrosec_ = tv.tv_usec + 1000000 * tv.tv_sec;
    lastEpochMicrosec_ = startEpochMicrosec_;
}


std::string XCommonEventHeaderImp::toString()
{
    try
    {
        auto js = toJson();
        return js.dump();
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to dump XCommonEventHeaderImp to json string:{}.", e.what());
        return "";
    }
}

void XCommonEventHeaderImp::setEventId(const XString& eventId)
{
    comVals_["eventId"] = eventId;
}

void XCommonEventHeaderImp::setReportingEntityId(const XString& reportingEntityId)
{
    comVals_["reportingEntityId"] = reportingEntityId;
}

void XCommonEventHeaderImp::setDomain(XEnumCommonEventHeaderDomain domain)
{
    auto val = XEnumCommonEventHeaderDomainMapping[domain];
    comVals_["domain"] = val;
}

void XCommonEventHeaderImp::setLastEpochMicrosec(XInteger lastEpochMicrosec)
{
    comVals_["lastEpochMicrosec"] = lastEpochMicrosec;
}

void XCommonEventHeaderImp::setReportingEntityName(const XString& reportingEntityName)
{
    comVals_["reportingEntityName"] = reportingEntityName;
}

void XCommonEventHeaderImp::setSourceId(const XString& sourceId)
{
    comVals_["sourceId"] = sourceId;
}

void XCommonEventHeaderImp::setEventType(const XString& eventType)
{
    comVals_["eventType"] = eventType;
}

void XCommonEventHeaderImp::setSequence(XInteger sequence)
{
    comVals_["sequence"] = sequence;
}

void XCommonEventHeaderImp::setInternalHeaderFields(const XInternalHeaderFields& internalHeaderFields)
{
    comVals_["internalHeaderFields"] = internalHeaderFields;
}

void XCommonEventHeaderImp::setPriority(XEnumCommonEventHeaderPriority priority)
{
    auto val = XEnumCommonEventHeaderPriorityMapping[priority];
    comVals_["priority"] = val;
}

void XCommonEventHeaderImp::setSourceName(const XString& sourceName)
{
    comVals_["sourceName"] = sourceName;
}

void XCommonEventHeaderImp::setEventName(const XString& eventName)
{
    comVals_["eventName"] = eventName;
}

void XCommonEventHeaderImp::setNfNamingCode(const XString& nfNamingCode)
{
    comVals_["nfNamingCode"] = nfNamingCode;
}

void XCommonEventHeaderImp::setStartEpochMicrosec(XInteger startEpochMicrosec)
{
    comVals_["startEpochMicrosec"] = startEpochMicrosec;
}

void XCommonEventHeaderImp::setNfVendorName(const XString& nfVendorName)
{
    comVals_["nfVendorName"] = nfVendorName;
}

void XCommonEventHeaderImp::setTimeZoneOffset(const XString& timeZoneOffset)
{
    comVals_["timeZoneOffset"] = timeZoneOffset;
}

void XCommonEventHeaderImp::setNfcNamingCode(const XString& nfcNamingCode)
{
    comVals_["nfcNamingCode"] = nfcNamingCode;
}

nlohmann::json XCommonEventHeaderImp::toJson()
{
    try
    {
        json field = {
            {"eventId", eventId_},
            {"domain", XEnumCommonEventHeaderDomainMapping[domain_]},
            {"lastEpochMicrosec", (unsigned long)(lastEpochMicrosec_)},
            {"reportingEntityName", reportingEntityName_},
            {"sequence", sequence_},
            {"priority", XEnumCommonEventHeaderPriorityMapping[priority_]},
            {"sourceName", sourceName_},
            {"eventName", eventName_},
            {"version", XEnumCommonEventHeaderVersionMapping[version_]},
            {"startEpochMicrosec", (unsigned long)(startEpochMicrosec_)},
            {"vesEventListenerVersion", XEnumCommonEventHeaderVesEventListenerVersionMapping[vesEventListenerVersion_]}
        };

        if (!internalHeaderFields_.empty())
        {
            field["internalHeaderFields"] = internalHeaderFields_;
        }
        //optVal
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XCommonEventHeaderImp to json object:{}.", e.what());
        return json();
    }
}
