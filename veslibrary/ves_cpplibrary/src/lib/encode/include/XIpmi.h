#pragma once
        
#include "XEvent.h"
#include "XIpmiFan.h"
#include "XIpmiProcessor.h"
#include "XIpmiBaseboardVoltageRegulator.h"
#include "XIpmiGlobalAggregateTemperatureMargin.h"
#include "XIpmiNic.h"
#include "XIpmiBaseboardTemperature.h"
#include "XIpmiPowerSupply.h"
#include "XIpmiHsbp.h"
#include "XIpmiBattery.h"

namespace vagt
{
    namespace encode
    {
        class XIpmi
        {
        public:
            XIpmi();

            virtual void setSystemAirflow(XNumber systemAirflow);
            virtual void setIpmiFanArray(const XArrayOfXIpmiFan& ipmiFanArray);
            virtual void setIpmiProcessorArray(const XArrayOfXIpmiProcessor& ipmiProcessorArray);
            virtual void setExitAirTemperature(XNumber exitAirTemperature);
            virtual void setIpmiBaseboardVoltageRegulatorArray(const XArrayOfXIpmiBaseboardVoltageRegulator& ipmiBaseboardVoltageRegulatorArray);
            virtual void setIpmiGlobalAggregateTemperatureMarginArray(const XArrayOfXIpmiGlobalAggregateTemperatureMargin& ipmiGlobalAggregateTemperatureMarginArray);
            virtual void setIpmiNicArray(const XArrayOfXIpmiNic& ipmiNicArray);
            virtual void setIpmiBaseboardTemperatureArray(const XArrayOfXIpmiBaseboardTemperature& ipmiBaseboardTemperatureArray);
            virtual void setIpmiPowerSupplyArray(const XArrayOfXIpmiPowerSupply& ipmiPowerSupplyArray);
            virtual void setIoModuleTemperature(XNumber ioModuleTemperature);
            virtual void setIpmiHsbpArray(const XArrayOfXIpmiHsbp& ipmiHsbpArray);
            virtual void setIpmiBatteryArray(const XArrayOfXIpmiBattery& ipmiBatteryArray);
            virtual void setFrontPanelTemperature(XNumber frontPanelTemperature);

            std::shared_ptr<XIpmi> imp_;

        protected:
            XIpmi(void*);
       };
    }
}
        