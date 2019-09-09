#pragma once

#include "XIpmi.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiImp : public XIpmi, public XJsonable
        {
        public:
            XIpmiImp();

            virtual json toJson() override;

            virtual void setSystemAirflow(XNumber systemAirflow) override;
            virtual void setIpmiFanArray(const XArrayOfXIpmiFan& ipmiFanArray) override;
            virtual void setIpmiProcessorArray(const XArrayOfXIpmiProcessor& ipmiProcessorArray) override;
            virtual void setExitAirTemperature(XNumber exitAirTemperature) override;
            virtual void setIpmiBaseboardVoltageRegulatorArray(const XArrayOfXIpmiBaseboardVoltageRegulator& ipmiBaseboardVoltageRegulatorArray) override;
            virtual void setIpmiGlobalAggregateTemperatureMarginArray(const XArrayOfXIpmiGlobalAggregateTemperatureMargin& ipmiGlobalAggregateTemperatureMarginArray) override;
            virtual void setIpmiNicArray(const XArrayOfXIpmiNic& ipmiNicArray) override;
            virtual void setIpmiBaseboardTemperatureArray(const XArrayOfXIpmiBaseboardTemperature& ipmiBaseboardTemperatureArray) override;
            virtual void setIpmiPowerSupplyArray(const XArrayOfXIpmiPowerSupply& ipmiPowerSupplyArray) override;
            virtual void setIoModuleTemperature(XNumber ioModuleTemperature) override;
            virtual void setIpmiHsbpArray(const XArrayOfXIpmiHsbp& ipmiHsbpArray) override;
            virtual void setIpmiBatteryArray(const XArrayOfXIpmiBattery& ipmiBatteryArray) override;
            virtual void setFrontPanelTemperature(XNumber frontPanelTemperature) override;

        private:
            //optional
            XArrayOfXIpmiFan ipmiFanArray_;
            XArrayOfXIpmiProcessor ipmiProcessorArray_;
            XArrayOfXIpmiBaseboardVoltageRegulator ipmiBaseboardVoltageRegulatorArray_;
            XArrayOfXIpmiGlobalAggregateTemperatureMargin ipmiGlobalAggregateTemperatureMarginArray_;
            XArrayOfXIpmiNic ipmiNicArray_;
            XArrayOfXIpmiBaseboardTemperature ipmiBaseboardTemperatureArray_;
            XArrayOfXIpmiPowerSupply ipmiPowerSupplyArray_;
            XArrayOfXIpmiHsbp ipmiHsbpArray_;
            XArrayOfXIpmiBattery ipmiBatteryArray_;
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        