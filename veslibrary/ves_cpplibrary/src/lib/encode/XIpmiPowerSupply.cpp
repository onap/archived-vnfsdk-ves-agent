#include "XIpmiPowerSupply.h"
#include "XIpmiPowerSupplyImp.h"

vagt::encode::XIpmiPowerSupply::XIpmiPowerSupply()
{
}

vagt::encode::XIpmiPowerSupply::XIpmiPowerSupply(const XString & powerSupplyIdentifier):
    imp_(make_shared<XIpmiPowerSupplyImp>(powerSupplyIdentifier))
{
}

void vagt::encode::XIpmiPowerSupply::setPowerSupplyInputPower(XNumber powerSupplyInputPower)
{
    return imp_->setPowerSupplyInputPower(powerSupplyInputPower);
}

void vagt::encode::XIpmiPowerSupply::setPowerSupplyCurrentOutputPercent(XNumber powerSupplyCurrentOutputPercent)
{
    return imp_->setPowerSupplyCurrentOutputPercent(powerSupplyCurrentOutputPercent);
}

void vagt::encode::XIpmiPowerSupply::setPowerSupplyIdentifier(const XString & powerSupplyIdentifier)
{
    return imp_->setPowerSupplyIdentifier(powerSupplyIdentifier);
}

void vagt::encode::XIpmiPowerSupply::setPowerSupplyTemperature(XNumber powerSupplyTemperature)
{
    return imp_->setPowerSupplyTemperature(powerSupplyTemperature);
}
