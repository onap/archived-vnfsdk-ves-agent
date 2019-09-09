#pragma once
        
#include "XSyslogFields.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XSyslogFieldsImp : public XSyslogFields, public XJsonable
        {
        public:
            XSyslogFieldsImp(std::shared_ptr<XCommonEventHeader> header,
                XEnumSyslogFieldsEventSourceType eventSourceType,
                const XString& syslogTag,
                const XString& syslogMsg
                );

            virtual std::string toString() override;

            virtual json toJson() override;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() override;

            virtual void setSyslogProcId(XNumber syslogProcId) override;
            virtual void setSyslogFacility(XInteger syslogFacility) override;
            virtual void setSyslogPri(XInteger syslogPri) override;
            virtual void setEventSourceType(XEnumSyslogFieldsEventSourceType eventSourceType) override;
            virtual void setSyslogMsgHost(const XString& syslogMsgHost) override;
            virtual void setSyslogSev(XEnumSyslogFieldsSyslogSev syslogSev) override;
            virtual void setSyslogSData(const XString& syslogSData) override;
            virtual void setSyslogMsg(const XString& syslogMsg) override;
            virtual void setSyslogProc(const XString& syslogProc) override;
            virtual void setEventSourceHost(const XString& eventSourceHost) override;
            virtual void setSyslogTs(const XString& syslogTs) override;
            virtual void setSyslogTag(const XString& syslogTag) override;
            virtual void setSyslogVer(XNumber syslogVer) override;
            virtual void setAdditionalFields(const XHashMap& additionalFields) override;
            virtual void setSyslogSdId(const XString& syslogSdId) override;

        private:
            //required
            std::shared_ptr<XCommonEventHeader> header_;
            XEnumSyslogFieldsEventSourceType eventSourceType_;
            XString syslogMsg_;
            XEnumSyslogFieldsSyslogFieldsVersion syslogFieldsVersion_;
            XString syslogTag_;
            //optional
            XEnumSyslogFieldsSyslogSev syslogSev_;
            XHashMap additionalFields_;
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        