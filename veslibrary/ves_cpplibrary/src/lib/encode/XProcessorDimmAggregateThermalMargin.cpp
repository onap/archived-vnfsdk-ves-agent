#include "XProcessorDimmAggregateThermalMargin.h"
#include "XProcessorDimmAggregateThermalMarginImp.h"

vagt::encode::XProcessorDimmAggregateThermalMargin::XProcessorDimmAggregateThermalMargin()
{
}

vagt::encode::XProcessorDimmAggregateThermalMargin::XProcessorDimmAggregateThermalMargin(const XString & processorDimmAggregateThermalMarginIdentifier, XNumber thermalMargin):
    imp_(make_shared<XProcessorDimmAggregateThermalMarginImp>(processorDimmAggregateThermalMarginIdentifier, thermalMargin))
{
}

void vagt::encode::XProcessorDimmAggregateThermalMargin::setProcessorDimmAggregateThermalMarginIdentifier(const XString & processorDimmAggregateThermalMarginIdentifier)
{
    return imp_->setProcessorDimmAggregateThermalMarginIdentifier(processorDimmAggregateThermalMarginIdentifier);
}

void vagt::encode::XProcessorDimmAggregateThermalMargin::setThermalMargin(XNumber thermalMargin)
{
    return imp_->setThermalMargin(thermalMargin);
}
