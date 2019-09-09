#pragma once
        
#include "XFaultFields.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XFaultFieldsImp : public XFaultFields, public XJsonable
        {
        public:
            XFaultFieldsImp(shared_ptr<XCommonEventHeader> header,
                const XString& alarmCondition,
                const XString& specificProblem,
                XEnumFaultFieldsEventSourceType eventSourceType,
                XEnumFaultFieldsEventSeverity eventSeverity,
                XEnumFaultFieldsVfStatus vfStatus);

            virtual std::string toString() override;
            virtual json toJson() override;
            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() override;

            virtual void setAlarmInterfaceA(const XString& alarmInterfaceA) override;
            virtual void setEventSeverity(XEnumFaultFieldsEventSeverity eventSeverity) override;
            virtual void setAlarmCondition(const XString& alarmCondition) override;
            virtual void setVfStatus(XEnumFaultFieldsVfStatus vfStatus) override;
            virtual void setEventCategory(const XString& eventCategory) override;
            virtual void setEventSourceType(XEnumFaultFieldsEventSourceType eventSourceType) override;
            virtual void setSpecificProblem(const XString& specificProblem) override;
            virtual void setAlarmAdditionalInformation(const XHashMap& alarmAdditionalInformation) override;

        private:
            //required
            shared_ptr<XCommonEventHeader> header_;
            XEnumFaultFieldsEventSeverity eventSeverity_;
            XString alarmCondition_;
            XEnumFaultFieldsVfStatus vfStatus_;
            XEnumFaultFieldsEventSourceType eventSourceType_;
            XString specificProblem_;
            XEnumFaultFieldsFaultFieldsVersion faultFieldsVersion_;
            //optional
            XHashMap alarmAdditionalInformation_;
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        