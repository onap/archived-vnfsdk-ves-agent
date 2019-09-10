#include "XIpmiFan.h"
#include "XIpmiFanImp.h"

vagt::encode::XIpmiFan::XIpmiFan()
{
}

vagt::encode::XIpmiFan::XIpmiFan(const XString & fanIdentifier):
    imp_(make_shared<XIpmiFanImp>(fanIdentifier))
{
}

void vagt::encode::XIpmiFan::setFanSpeed(XNumber fanSpeed)
{
    return imp_->setFanSpeed(fanSpeed);
}

void vagt::encode::XIpmiFan::setFanIdentifier(const XString & fanIdentifier)
{
    return imp_->setFanIdentifier(fanIdentifier);
}
