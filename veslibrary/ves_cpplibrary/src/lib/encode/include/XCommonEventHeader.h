#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        using XInternalHeaderFields = std::string;

        enum XEnumCommonEventHeaderVersion
        {
            XEnumCommonEventHeaderVersion4_0_1,
        };

        enum XEnumCommonEventHeaderVesEventListenerVersion
        {
            XEnumCommonEventHeaderVesEventListenerVersion7_0_1,
        };

        enum XEnumCommonEventHeaderDomain
        {
            XEnumCommonEventHeaderDomainFault,
            XEnumCommonEventHeaderDomainHeartbeat,
            XEnumCommonEventHeaderDomainMeasurement,
            XEnumCommonEventHeaderDomainMobileFlow,
            XEnumCommonEventHeaderDomainNotification,
            XEnumCommonEventHeaderDomainOther,
            XEnumCommonEventHeaderDomainPnfRegistration,
            XEnumCommonEventHeaderDomainSipSignaling,
            XEnumCommonEventHeaderDomainStateChange,
            XEnumCommonEventHeaderDomainSyslog,
            XEnumCommonEventHeaderDomainThresholdCrossingAlert,
            XEnumCommonEventHeaderDomainVoiceQuality,
        };

        enum XEnumCommonEventHeaderPriority
        {
            XEnumCommonEventHeaderPriorityHigh,
            XEnumCommonEventHeaderPriorityMedium,
            XEnumCommonEventHeaderPriorityNormal,
            XEnumCommonEventHeaderPriorityLow,
        };

        class XCommonEventHeader : public XSerialable
        {
        public:
            virtual std::string toString() = 0;

            virtual void setEventId(const XString& eventId) = 0;
            virtual void setReportingEntityId(const XString& reportingEntityId) = 0;
            virtual void setDomain(XEnumCommonEventHeaderDomain domain) = 0;
            virtual void setLastEpochMicrosec(XInteger lastEpochMicrosec) = 0;
            virtual void setReportingEntityName(const XString& reportingEntityName) = 0;
            virtual void setSourceId(const XString& sourceId) = 0;
            virtual void setEventType(const XString& eventType) = 0;
            virtual void setSequence(XInteger sequence) = 0;
            virtual void setInternalHeaderFields(const XInternalHeaderFields& internalHeaderFields) = 0;
            virtual void setPriority(XEnumCommonEventHeaderPriority priority) = 0;
            virtual void setSourceName(const XString& sourceName) = 0;
            virtual void setEventName(const XString& eventName) = 0;
            virtual void setNfNamingCode(const XString& nfNamingCode) = 0;
            virtual void setStartEpochMicrosec(XInteger startEpochMicrosec) = 0;
            virtual void setNfVendorName(const XString& nfVendorName) = 0;
            virtual void setTimeZoneOffset(const XString& timeZoneOffset) = 0;
            virtual void setNfcNamingCode(const XString& nfcNamingCode) = 0;

            static std::shared_ptr<XCommonEventHeader> create(const XString& eventName,
                const XString& eventId,
                const XString& sourceName,
                const XString& reportingEntityName,
                XEnumCommonEventHeaderPriority priority,
                XInteger sequence);
        };

        class XExtendEvent : public XSerialable
        {
        public:
            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() = 0;
        };
    }
}
        
