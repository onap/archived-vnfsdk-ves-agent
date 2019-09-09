#include "XKey.h"
#include "XKeyImp.h"

vagt::encode::XKey::XKey()
{
}

vagt::encode::XKey::XKey(const XString & keyName):
    imp_(make_shared<XKeyImp>(keyName))
{
}

void vagt::encode::XKey::setKeyValue(const XString & keyValue)
{
    return imp_->setKeyValue(keyValue);
}

void vagt::encode::XKey::setKeyOrder(XInteger keyOrder)
{
    return imp_->setKeyOrder(keyOrder);
}

void vagt::encode::XKey::setKeyName(const XString & keyName)
{
    return imp_->setKeyName(keyName);
}
