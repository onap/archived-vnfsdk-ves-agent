#include "XCodecsInUse.h"
#include "XCodecsInUseImp.h"

vagt::encode::XCodecsInUse::XCodecsInUse()
{
}

vagt::encode::XCodecsInUse::XCodecsInUse(const XString & codecIdentifier, XInteger numberInUse):
    imp_(make_shared<XCodecsInUseImp>(codecIdentifier, numberInUse))
{
}

void vagt::encode::XCodecsInUse::setCodecIdentifier(const XString & codecIdentifier)
{
    return imp_->setCodecIdentifier(codecIdentifier);
}

void vagt::encode::XCodecsInUse::setNumberInUse(XInteger numberInUse)
{
    return imp_->setNumberInUse(numberInUse);
}
