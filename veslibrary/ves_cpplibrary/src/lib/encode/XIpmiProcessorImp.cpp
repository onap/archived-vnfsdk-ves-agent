#include "XIpmiProcessorImp.h"

XIpmiProcessorImp::XIpmiProcessorImp(const XString& processorIdentifier):
        processorIdentifier_(processorIdentifier)
{

}

void XIpmiProcessorImp::setProcessorThermalControlPercent(XNumber processorThermalControlPercent)
{
    comVals_["processorThermalControlPercent"] = processorThermalControlPercent;
}
            
void XIpmiProcessorImp::setProcessorDtsThermalMargin(XNumber processorDtsThermalMargin)
{
    comVals_["processorDtsThermalMargin"] = processorDtsThermalMargin;
}
            
void XIpmiProcessorImp::setProcessorIdentifier(const XString& processorIdentifier)
{
    comVals_["processorIdentifier"] = processorIdentifier;
}
            
void XIpmiProcessorImp::setProcessorDimmAggregateThermalMarginArray(const XArrayOfXProcessorDimmAggregateThermalMargin& processorDimmAggregateThermalMarginArray)
{
    processorDimmAggregateThermalMarginArray_ = processorDimmAggregateThermalMarginArray;
}

json XIpmiProcessorImp::toJson()
{
    try
    {
        json field = {
            {"processorIdentifier", processorIdentifier_}
        };

        //optional val
        if (!processorDimmAggregateThermalMarginArray_.empty())
        {
            field["processorDimmAggregateThermalMarginArray"] = fromArray(processorDimmAggregateThermalMarginArray_);
        }
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XIpmiProcessor to json object:{}.", e.what());
        return json();
    }
}
            