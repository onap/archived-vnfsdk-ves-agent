#include "XProcessorDimmAggregateThermalMarginImp.h"

XProcessorDimmAggregateThermalMarginImp::XProcessorDimmAggregateThermalMarginImp(const XString& processorDimmAggregateThermalMarginIdentifier,
    XNumber thermalMargin):
        processorDimmAggregateThermalMarginIdentifier_(processorDimmAggregateThermalMarginIdentifier),
        thermalMargin_(thermalMargin)
{

}

void XProcessorDimmAggregateThermalMarginImp::setProcessorDimmAggregateThermalMarginIdentifier(const XString& processorDimmAggregateThermalMarginIdentifier)
{
    comVals_["processorDimmAggregateThermalMarginIdentifier"] = processorDimmAggregateThermalMarginIdentifier;
}
            
void XProcessorDimmAggregateThermalMarginImp::setThermalMargin(XNumber thermalMargin)
{
    comVals_["thermalMargin"] = thermalMargin;
}

json XProcessorDimmAggregateThermalMarginImp::toJson()
{
    try
    {
        json field = {
            {"processorDimmAggregateThermalMarginIdentifier", processorDimmAggregateThermalMarginIdentifier_},
            {"thermalMargin", thermalMargin_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XProcessorDimmAggregateThermalMargin to json object:{}.", e.what());
        return json();
    }
}
            