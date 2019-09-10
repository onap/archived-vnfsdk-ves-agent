#include "XIpmiProcessor.h"
#include "XIpmiProcessorImp.h"

vagt::encode::XIpmiProcessor::XIpmiProcessor()
{
}

vagt::encode::XIpmiProcessor::XIpmiProcessor(const XString & processorIdentifier):
    imp_(make_shared<XIpmiProcessorImp>(processorIdentifier))
{
}

void vagt::encode::XIpmiProcessor::setProcessorThermalControlPercent(XNumber processorThermalControlPercent)
{
    return imp_->setProcessorThermalControlPercent(processorThermalControlPercent);
}

void vagt::encode::XIpmiProcessor::setProcessorDtsThermalMargin(XNumber processorDtsThermalMargin)
{
    return imp_->setProcessorDtsThermalMargin(processorDtsThermalMargin);
}

void vagt::encode::XIpmiProcessor::setProcessorIdentifier(const XString & processorIdentifier)
{
    return imp_->setProcessorIdentifier(processorIdentifier);
}

void vagt::encode::XIpmiProcessor::setProcessorDimmAggregateThermalMarginArray(const XArrayOfXProcessorDimmAggregateThermalMargin & processorDimmAggregateThermalMarginArray)
{
    return imp_->setProcessorDimmAggregateThermalMarginArray(processorDimmAggregateThermalMarginArray);
}
