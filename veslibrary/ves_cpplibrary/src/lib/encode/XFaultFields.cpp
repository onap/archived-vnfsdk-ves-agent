#include "XFaultFields.h"
#include "XFaultFieldsImp.h"

std::shared_ptr<XFaultFields> vagt::encode::XFaultFields::create(std::shared_ptr<XCommonEventHeader> header, const XString & alarmCondition, const XString & specificProblem, XEnumFaultFieldsEventSourceType eventSourceType, XEnumFaultFieldsEventSeverity eventSeverity, XEnumFaultFieldsVfStatus vfStatus)
{
    return std::make_shared<XFaultFieldsImp>(header,
        alarmCondition,
        specificProblem,
        eventSourceType,
        eventSeverity,
        vfStatus
        );
}
