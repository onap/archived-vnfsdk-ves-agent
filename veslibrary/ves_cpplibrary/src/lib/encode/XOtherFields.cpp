#include "XOtherFields.h"
#include "XOtherFieldsImp.h"

std::shared_ptr<XOtherFields> vagt::encode::XOtherFields::create(std::shared_ptr<XCommonEventHeader> header)
{
    return std::make_shared<XOtherFieldsImp>(header);
}
