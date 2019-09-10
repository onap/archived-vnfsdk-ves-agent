#include "XIpmiImp.h"

XIpmiImp::XIpmiImp():XIpmi(nullptr)
{
}

void XIpmiImp::setSystemAirflow(XNumber systemAirflow)
{
    comVals_["systemAirflow"] = systemAirflow;
}
            
void XIpmiImp::setIpmiFanArray(const XArrayOfXIpmiFan& ipmiFanArray)
{
    ipmiFanArray_ = ipmiFanArray;
}
            
void XIpmiImp::setIpmiProcessorArray(const XArrayOfXIpmiProcessor& ipmiProcessorArray)
{
    ipmiProcessorArray_ = ipmiProcessorArray;
}
            
void XIpmiImp::setExitAirTemperature(XNumber exitAirTemperature)
{
    comVals_["exitAirTemperature"] = exitAirTemperature;
}
            
void XIpmiImp::setIpmiBaseboardVoltageRegulatorArray(const XArrayOfXIpmiBaseboardVoltageRegulator& ipmiBaseboardVoltageRegulatorArray)
{
    ipmiBaseboardVoltageRegulatorArray_ = ipmiBaseboardVoltageRegulatorArray;
}
            
void XIpmiImp::setIpmiGlobalAggregateTemperatureMarginArray(const XArrayOfXIpmiGlobalAggregateTemperatureMargin& ipmiGlobalAggregateTemperatureMarginArray)
{
    ipmiGlobalAggregateTemperatureMarginArray_ = ipmiGlobalAggregateTemperatureMarginArray;
}
            
void XIpmiImp::setIpmiNicArray(const XArrayOfXIpmiNic& ipmiNicArray)
{
    ipmiNicArray_ = ipmiNicArray;
}
            
void XIpmiImp::setIpmiBaseboardTemperatureArray(const XArrayOfXIpmiBaseboardTemperature& ipmiBaseboardTemperatureArray)
{
    ipmiBaseboardTemperatureArray_ = ipmiBaseboardTemperatureArray;
}
            
void XIpmiImp::setIpmiPowerSupplyArray(const XArrayOfXIpmiPowerSupply& ipmiPowerSupplyArray)
{
    ipmiPowerSupplyArray_ = ipmiPowerSupplyArray;
}
            
void XIpmiImp::setIoModuleTemperature(XNumber ioModuleTemperature)
{
    comVals_["ioModuleTemperature"] = ioModuleTemperature;
}
            
void XIpmiImp::setIpmiHsbpArray(const XArrayOfXIpmiHsbp& ipmiHsbpArray)
{
    ipmiHsbpArray_ = ipmiHsbpArray;
}
            
void XIpmiImp::setIpmiBatteryArray(const XArrayOfXIpmiBattery& ipmiBatteryArray)
{
    ipmiBatteryArray_ = ipmiBatteryArray;
}
            
void XIpmiImp::setFrontPanelTemperature(XNumber frontPanelTemperature)
{
    comVals_["frontPanelTemperature"] = frontPanelTemperature;
}

json XIpmiImp::toJson()
{
    try
    {
        json field;

        //optional val
        if (!ipmiFanArray_.empty())
        {
            field["ipmiFanArray"] = fromArray(ipmiFanArray_);
        }

        if (!ipmiProcessorArray_.empty())
        {
            field["ipmiProcessorArray"] = fromArray(ipmiProcessorArray_);
        }

        if (!ipmiBaseboardVoltageRegulatorArray_.empty())
        {
            field["ipmiBaseboardVoltageRegulatorArray"] = fromArray(ipmiBaseboardVoltageRegulatorArray_);
        }

        if (!ipmiGlobalAggregateTemperatureMarginArray_.empty())
        {
            field["ipmiGlobalAggregateTemperatureMarginArray"] = fromArray(ipmiGlobalAggregateTemperatureMarginArray_);
        }

        if (!ipmiNicArray_.empty())
        {
            field["ipmiNicArray"] = fromArray(ipmiNicArray_);
        }

        if (!ipmiBaseboardTemperatureArray_.empty())
        {
            field["ipmiBaseboardTemperatureArray"] = fromArray(ipmiBaseboardTemperatureArray_);
        }

        if (!ipmiPowerSupplyArray_.empty())
        {
            field["ipmiPowerSupplyArray"] = fromArray(ipmiPowerSupplyArray_);
        }

        if (!ipmiHsbpArray_.empty())
        {
            field["ipmiHsbpArray"] = fromArray(ipmiHsbpArray_);
        }

        if (!ipmiBatteryArray_.empty())
        {
            field["ipmiBatteryArray"] = fromArray(ipmiBatteryArray_);
        }

        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XIpmi to json object:{}.", e.what());
        return json();
    }
}
            