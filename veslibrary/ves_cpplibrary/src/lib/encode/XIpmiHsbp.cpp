#include "XIpmiHsbp.h"
#include "XIpmiHsbpImp.h"

vagt::encode::XIpmiHsbp::XIpmiHsbp()
{
}

vagt::encode::XIpmiHsbp::XIpmiHsbp(const XString & hsbpIdentifier):
    imp_(make_shared<XIpmiHsbpImp>(hsbpIdentifier))
{
}

void vagt::encode::XIpmiHsbp::setHsbpTemperature(XNumber hsbpTemperature)
{
    return imp_->setHsbpTemperature(hsbpTemperature);
}

void vagt::encode::XIpmiHsbp::setHsbpIdentifier(const XString & hsbpIdentifier)
{
    return imp_->setHsbpIdentifier(hsbpIdentifier);
}
