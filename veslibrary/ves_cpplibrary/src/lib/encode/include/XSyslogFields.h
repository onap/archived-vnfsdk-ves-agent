#pragma once
        
#include "XCommonEventHeader.h"

namespace vagt
{
    namespace encode
    {
        enum XEnumSyslogFieldsSyslogFieldsVersion
        {
            XEnumSyslogFieldsSyslogFieldsVersion4_0,
        };

        enum XEnumSyslogFieldsSyslogSev
        {
            XEnumSyslogFieldsSyslogSevAlert,
            XEnumSyslogFieldsSyslogSevCritical,
            XEnumSyslogFieldsSyslogSevDebug,
            XEnumSyslogFieldsSyslogSevEmergency,
            XEnumSyslogFieldsSyslogSevError,
            XEnumSyslogFieldsSyslogSevInfo,
            XEnumSyslogFieldsSyslogSevNotice,
            XEnumSyslogFieldsSyslogSevWarning,
        };

        enum XEnumSyslogFieldsEventSourceType
        {
            XEnumSyslogFieldsEventSourceTypeOther,
            XEnumSyslogFieldsEventSourceTypeRouter,
            XEnumSyslogFieldsEventSourceTypeSwitch,
            XEnumSyslogFieldsEventSourceTypeHost,
            XEnumSyslogFieldsEventSourceTypeCard,
            XEnumSyslogFieldsEventSourceTypePort,
            XEnumSyslogFieldsEventSourceTypeSlotThreshold,
            XEnumSyslogFieldsEventSourceTypePortThreshold,
            XEnumSyslogFieldsEventSourceTypeVirtualMachine,
            XEnumSyslogFieldsEventSourceTypeVirtualNetworkFunction,
        };

        class XSyslogFields : public XExtendEvent
        {
        public:
            virtual std::string toString() = 0;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() = 0;

            virtual void setSyslogProcId(XNumber syslogProcId) = 0;
            virtual void setSyslogFacility(XInteger syslogFacility) = 0;
            virtual void setSyslogPri(XInteger syslogPri) = 0;
            virtual void setEventSourceType(XEnumSyslogFieldsEventSourceType eventSourceType) = 0;
            virtual void setSyslogMsgHost(const XString& syslogMsgHost) = 0;
            virtual void setSyslogSev(XEnumSyslogFieldsSyslogSev syslogSev) = 0;
            virtual void setSyslogSData(const XString& syslogSData) = 0;
            virtual void setSyslogMsg(const XString& syslogMsg) = 0;
            virtual void setSyslogProc(const XString& syslogProc) = 0;
            virtual void setEventSourceHost(const XString& eventSourceHost) = 0;
            virtual void setSyslogTs(const XString& syslogTs) = 0;
            virtual void setSyslogTag(const XString& syslogTag) = 0;
            virtual void setSyslogVer(XNumber syslogVer) = 0;
            virtual void setAdditionalFields(const XHashMap& additionalFields) = 0;
            virtual void setSyslogSdId(const XString& syslogSdId) = 0;

            static std::shared_ptr<XSyslogFields> create(std::shared_ptr<XCommonEventHeader> header,
                XEnumSyslogFieldsEventSourceType eventSourceType,
                const XString& syslogTag,
                const XString& syslogMsg
                );
        };
    }
}
        