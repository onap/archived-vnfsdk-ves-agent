#include "XHeartbeatFields.h"
#include "XHeartbeatFieldsImp.h"

std::shared_ptr<XHeartbeatFields> vagt::encode::XHeartbeatFields::create(std::shared_ptr<XCommonEventHeader> header, XInteger heartbeatInterval)
{
    return std::make_shared<XHeartbeatFieldsImp>(header, heartbeatInterval);
}
