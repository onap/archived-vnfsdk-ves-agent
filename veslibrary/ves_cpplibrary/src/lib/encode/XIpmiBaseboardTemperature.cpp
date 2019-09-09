#include "XIpmiBaseboardTemperature.h"
#include "XIpmiBaseboardTemperatureImp.h"

vagt::encode::XIpmiBaseboardTemperature::XIpmiBaseboardTemperature()
{
}

vagt::encode::XIpmiBaseboardTemperature::XIpmiBaseboardTemperature(const XString & baseboardTemperatureIdentifier):
    imp_(make_shared<XIpmiBaseboardTemperatureImp>(baseboardTemperatureIdentifier))
{
}

void vagt::encode::XIpmiBaseboardTemperature::setBaseboardTemperature(XNumber baseboardTemperature)
{
    return imp_->setBaseboardTemperature(baseboardTemperature);
}

void vagt::encode::XIpmiBaseboardTemperature::setBaseboardTemperatureIdentifier(const XString & baseboardTemperatureIdentifier)
{
    return imp_->setBaseboardTemperatureIdentifier(baseboardTemperatureIdentifier);
}
