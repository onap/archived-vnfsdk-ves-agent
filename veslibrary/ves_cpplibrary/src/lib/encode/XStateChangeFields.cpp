#include "XStateChangeFields.h"
#include "XStateChangeFieldsImp.h"

std::shared_ptr<XStateChangeFields> vagt::encode::XStateChangeFields::create(std::shared_ptr<XCommonEventHeader> header, XEnumStateChangeFieldsState newState, XEnumStateChangeFieldsState oldState, const XString & stateInterface)
{
    return std::make_shared<XStateChangeFieldsImp>(header, newState, oldState, stateInterface);
}
