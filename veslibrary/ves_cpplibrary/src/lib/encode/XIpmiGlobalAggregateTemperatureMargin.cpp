#include "XIpmiGlobalAggregateTemperatureMargin.h"
#include "XIpmiGlobalAggregateTemperatureMarginImp.h"

vagt::encode::XIpmiGlobalAggregateTemperatureMargin::XIpmiGlobalAggregateTemperatureMargin()
{
}

vagt::encode::XIpmiGlobalAggregateTemperatureMargin::XIpmiGlobalAggregateTemperatureMargin(const XString & ipmiGlobalAggregateTemperatureMarginIdentifier, XNumber globalAggregateTemperatureMargin):
    imp_(make_shared<XIpmiGlobalAggregateTemperatureMarginImp>(ipmiGlobalAggregateTemperatureMarginIdentifier, globalAggregateTemperatureMargin))
{
}

void vagt::encode::XIpmiGlobalAggregateTemperatureMargin::setIpmiGlobalAggregateTemperatureMarginIdentifier(const XString & ipmiGlobalAggregateTemperatureMarginIdentifier)
{
    return imp_->setIpmiGlobalAggregateTemperatureMarginIdentifier(ipmiGlobalAggregateTemperatureMarginIdentifier);
}

void vagt::encode::XIpmiGlobalAggregateTemperatureMargin::setGlobalAggregateTemperatureMargin(XNumber globalAggregateTemperatureMargin)
{
    return imp_->setGlobalAggregateTemperatureMargin(globalAggregateTemperatureMargin);
}
