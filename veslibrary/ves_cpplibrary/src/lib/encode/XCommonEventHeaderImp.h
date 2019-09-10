#pragma once
        
#include "XCommonEventHeader.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XCommonEventHeaderImp : public XCommonEventHeader, public XJsonable
        {
        public:
            XCommonEventHeaderImp(
                const XString& eventName,
                const XString& eventId,
                const XString& sourceName,
                const XString& reportingEntityName,
                XEnumCommonEventHeaderPriority priority,
                XInteger sequence);

            virtual std::string toString() override;

            virtual nlohmann::json toJson() override;

            virtual void setEventId(const XString& eventId) override;
            virtual void setReportingEntityId(const XString& reportingEntityId) override;
            virtual void setDomain(XEnumCommonEventHeaderDomain domain) override;
            virtual void setLastEpochMicrosec(XInteger lastEpochMicrosec) override;
            virtual void setReportingEntityName(const XString& reportingEntityName) override;
            virtual void setSourceId(const XString& sourceId) override;
            virtual void setEventType(const XString& eventType) override;
            virtual void setSequence(XInteger sequence) override;
            virtual void setInternalHeaderFields(const XInternalHeaderFields& internalHeaderFields) override;
            virtual void setPriority(XEnumCommonEventHeaderPriority priority) override;
            virtual void setSourceName(const XString& sourceName) override;
            virtual void setEventName(const XString& eventName) override;
            virtual void setNfNamingCode(const XString& nfNamingCode) override;
            virtual void setStartEpochMicrosec(XInteger startEpochMicrosec) override;
            virtual void setNfVendorName(const XString& nfVendorName) override;
            virtual void setTimeZoneOffset(const XString& timeZoneOffset) override;
            virtual void setNfcNamingCode(const XString& nfcNamingCode) override;

        private:
            //required
            XString eventId_;
            XEnumCommonEventHeaderDomain domain_;
            XInteger startEpochMicrosec_;
            XInteger lastEpochMicrosec_;
            XString reportingEntityName_;
            XInteger sequence_;
            XEnumCommonEventHeaderPriority priority_;
            XString sourceName_;
            XString eventName_;
            XEnumCommonEventHeaderVersion version_;
            XEnumCommonEventHeaderVesEventListenerVersion vesEventListenerVersion_;
            //optional
            XInternalHeaderFields internalHeaderFields_;
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        