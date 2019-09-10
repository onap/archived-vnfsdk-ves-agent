#include "XIpmiNic.h"
#include "XIpmiNicImp.h"

vagt::encode::XIpmiNic::XIpmiNic()
{
}

vagt::encode::XIpmiNic::XIpmiNic(const XString & nicIdentifier):
    imp_(make_shared<XIpmiNicImp>(nicIdentifier))
{
}

void vagt::encode::XIpmiNic::setNicIdentifier(const XString & nicIdentifier)
{
    return imp_->setNicIdentifier(nicIdentifier);
}

void vagt::encode::XIpmiNic::setNicTemperature(XNumber nicTemperature)
{
    return imp_->setNicTemperature(nicTemperature);
}
