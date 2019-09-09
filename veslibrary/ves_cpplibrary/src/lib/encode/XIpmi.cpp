#include "XIpmi.h"
#include "XIpmiImp.h"

vagt::encode::XIpmi::XIpmi(void*)
{
}

vagt::encode::XIpmi::XIpmi():
    imp_(make_shared<XIpmiImp>())
{

}

void vagt::encode::XIpmi::setSystemAirflow(XNumber systemAirflow)
{
    return imp_->setSystemAirflow(systemAirflow);
}

void vagt::encode::XIpmi::setIpmiFanArray(const XArrayOfXIpmiFan & ipmiFanArray)
{
    return imp_->setIpmiFanArray(ipmiFanArray);
}

void vagt::encode::XIpmi::setIpmiProcessorArray(const XArrayOfXIpmiProcessor & ipmiProcessorArray)
{
    return imp_->setIpmiProcessorArray(ipmiProcessorArray);
}

void vagt::encode::XIpmi::setExitAirTemperature(XNumber exitAirTemperature)
{
    return imp_->setExitAirTemperature(exitAirTemperature);
}

void vagt::encode::XIpmi::setIpmiBaseboardVoltageRegulatorArray(const XArrayOfXIpmiBaseboardVoltageRegulator & ipmiBaseboardVoltageRegulatorArray)
{
    return imp_->setIpmiBaseboardVoltageRegulatorArray(ipmiBaseboardVoltageRegulatorArray);
}

void vagt::encode::XIpmi::setIpmiGlobalAggregateTemperatureMarginArray(const XArrayOfXIpmiGlobalAggregateTemperatureMargin & ipmiGlobalAggregateTemperatureMarginArray)
{
    return imp_->setIpmiGlobalAggregateTemperatureMarginArray(ipmiGlobalAggregateTemperatureMarginArray);
}

void vagt::encode::XIpmi::setIpmiNicArray(const XArrayOfXIpmiNic & ipmiNicArray)
{
    return imp_->setIpmiNicArray(ipmiNicArray);
}

void vagt::encode::XIpmi::setIpmiBaseboardTemperatureArray(const XArrayOfXIpmiBaseboardTemperature & ipmiBaseboardTemperatureArray)
{
    return imp_->setIpmiBaseboardTemperatureArray(ipmiBaseboardTemperatureArray);
}

void vagt::encode::XIpmi::setIpmiPowerSupplyArray(const XArrayOfXIpmiPowerSupply & ipmiPowerSupplyArray)
{
    return imp_->setIpmiPowerSupplyArray(ipmiPowerSupplyArray);
}

void vagt::encode::XIpmi::setIoModuleTemperature(XNumber ioModuleTemperature)
{
    return imp_->setIoModuleTemperature(ioModuleTemperature);
}

void vagt::encode::XIpmi::setIpmiHsbpArray(const XArrayOfXIpmiHsbp & ipmiHsbpArray)
{
    return imp_->setIpmiHsbpArray(ipmiHsbpArray);
}

void vagt::encode::XIpmi::setIpmiBatteryArray(const XArrayOfXIpmiBattery & ipmiBatteryArray)
{
    return imp_->setIpmiBatteryArray(ipmiBatteryArray);
}

void vagt::encode::XIpmi::setFrontPanelTemperature(XNumber frontPanelTemperature)
{
    return imp_->setFrontPanelTemperature(frontPanelTemperature);
}
