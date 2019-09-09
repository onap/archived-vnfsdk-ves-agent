#include "XPnfRegistrationFields.h"
#include "XPnfRegistrationFieldsImp.h"

std::shared_ptr<XPnfRegistrationFields> vagt::encode::XPnfRegistrationFields::create(std::shared_ptr<XCommonEventHeader> header)
{
    return std::make_shared<XPnfRegistrationFieldsImp>(header);
}
