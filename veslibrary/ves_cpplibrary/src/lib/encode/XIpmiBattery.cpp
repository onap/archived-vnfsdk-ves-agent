#include "XIpmiBattery.h"
#include "XIpmiBatteryImp.h"

vagt::encode::XIpmiBattery::XIpmiBattery()
{
}

vagt::encode::XIpmiBattery::XIpmiBattery(const XString & batteryIdentifier):
    imp_(make_shared<XIpmiBatteryImp>(batteryIdentifier))
{
}

void vagt::encode::XIpmiBattery::setBatteryType(const XString & batteryType)
{
    return imp_->setBatteryType(batteryType);
}

void vagt::encode::XIpmiBattery::setBatteryIdentifier(const XString & batteryIdentifier)
{
    return imp_->setBatteryIdentifier(batteryIdentifier);
}

void vagt::encode::XIpmiBattery::setBatteryVoltageLevel(XNumber batteryVoltageLevel)
{
    return imp_->setBatteryVoltageLevel(batteryVoltageLevel);
}
