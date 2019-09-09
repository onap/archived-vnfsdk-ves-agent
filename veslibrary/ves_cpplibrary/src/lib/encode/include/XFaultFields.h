#pragma once
        
#include "XCommonEventHeader.h"

namespace vagt
{
    namespace encode
    {
        enum XEnumFaultFieldsFaultFieldsVersion
        {
            XEnumFaultFieldsFaultFieldsVersion4_0,
        };

        enum XEnumFaultFieldsEventSeverity
        {
            XEnumFaultFieldsEventSeverityCRITICAL,
            XEnumFaultFieldsEventSeverityMAJOR,
            XEnumFaultFieldsEventSeverityMINOR,
            XEnumFaultFieldsEventSeverityWARNING,
            XEnumFaultFieldsEventSeverityNORMAL,
        };

        enum XEnumFaultFieldsVfStatus
        {
            XEnumFaultFieldsVfStatusActive,
            XEnumFaultFieldsVfStatusIdle,
            XEnumFaultFieldsVfStatusPreparingToTerminate,
            XEnumFaultFieldsVfStatusReadyToTerminate,
            XEnumFaultFieldsVfStatusRequestingTermination,
        };

        enum XEnumFaultFieldsEventSourceType
        {
            XEnumFaultFieldsEventSourceTypeOther,
            XEnumFaultFieldsEventSourceTypeRouter,
            XEnumFaultFieldsEventSourceTypeSwitch,
            XEnumFaultFieldsEventSourceTypeHost,
            XEnumFaultFieldsEventSourceTypeCard,
            XEnumFaultFieldsEventSourceTypePort,
            XEnumFaultFieldsEventSourceTypeSlotThreshold,
            XEnumFaultFieldsEventSourceTypePortThreshold,
            XEnumFaultFieldsEventSourceTypeVirtualMachine,
            XEnumFaultFieldsEventSourceTypeVirtualNetworkFunction,
        };

        class XFaultFields : public XExtendEvent
        {
        public:
            virtual std::string toString() = 0;
            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() = 0;

            virtual void setAlarmInterfaceA(const XString& alarmInterfaceA) = 0;
            virtual void setEventSeverity(XEnumFaultFieldsEventSeverity eventSeverity) = 0;
            virtual void setAlarmCondition(const XString& alarmCondition) = 0;
            virtual void setVfStatus(XEnumFaultFieldsVfStatus vfStatus) = 0;
            virtual void setEventCategory(const XString& eventCategory) = 0;
            virtual void setEventSourceType(XEnumFaultFieldsEventSourceType eventSourceType) = 0;
            virtual void setSpecificProblem(const XString& specificProblem) = 0;
            virtual void setAlarmAdditionalInformation(const XHashMap& alarmAdditionalInformation) = 0;

            static std::shared_ptr<XFaultFields> create(std::shared_ptr<XCommonEventHeader> header,
                const XString& alarmCondition,
                const XString& specificProblem,
                XEnumFaultFieldsEventSourceType eventSourceType,
                XEnumFaultFieldsEventSeverity eventSeverity,
                XEnumFaultFieldsVfStatus vfStatus);
        };
    }
}
        