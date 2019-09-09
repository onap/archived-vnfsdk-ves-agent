#include "XNotificationFields.h"
#include "XNotificationFieldsImp.h"

std::shared_ptr<XNotificationFields> vagt::encode::XNotificationFields::create(std::shared_ptr<XCommonEventHeader> header, const XString & changeIdentifier, const XString & changeType)
{
    return std::make_shared<XNotificationFieldsImp>(header, changeIdentifier, changeType);
}
