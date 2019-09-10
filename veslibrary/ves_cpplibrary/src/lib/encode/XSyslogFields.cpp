#include "XSyslogFields.h"
#include "XSyslogFieldsImp.h"

std::shared_ptr<XSyslogFields> vagt::encode::XSyslogFields::create(std::shared_ptr<XCommonEventHeader> header, XEnumSyslogFieldsEventSourceType eventSourceType, const XString & syslogTag, const XString & syslogMsg)
{
    return std::make_shared<XSyslogFieldsImp>(header, eventSourceType, syslogTag, syslogMsg);
}
