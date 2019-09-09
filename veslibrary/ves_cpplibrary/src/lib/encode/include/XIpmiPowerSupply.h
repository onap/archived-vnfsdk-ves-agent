#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiPowerSupply  
        {
        public:
            XIpmiPowerSupply(const XString& powerSupplyIdentifier);

            virtual void setPowerSupplyInputPower(XNumber powerSupplyInputPower);
            virtual void setPowerSupplyCurrentOutputPercent(XNumber powerSupplyCurrentOutputPercent);
            virtual void setPowerSupplyIdentifier(const XString& powerSupplyIdentifier);
            virtual void setPowerSupplyTemperature(XNumber powerSupplyTemperature);

            std::shared_ptr<XIpmiPowerSupply> imp_;

        protected:
            XIpmiPowerSupply();
        };

        using XArrayOfXIpmiPowerSupply = std::vector<XIpmiPowerSupply>;
    }
}
        