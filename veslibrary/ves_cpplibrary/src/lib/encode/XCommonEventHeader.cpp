#include "XCommonEventHeader.h"
#include "XCommonEventHeaderImp.h"

std::shared_ptr<XCommonEventHeader> vagt::encode::XCommonEventHeader::create(const XString & eventName, const XString & eventId, const XString & sourceName, const XString & reportingEntityName, XEnumCommonEventHeaderPriority priority, XInteger sequence)
{
    return std::make_shared<XCommonEventHeaderImp>(eventName,
        eventId,
        sourceName,
        reportingEntityName,
        priority,
        sequence
        );
}
