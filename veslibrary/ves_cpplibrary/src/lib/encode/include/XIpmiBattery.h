#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiBattery 
        {
        public:
            XIpmiBattery(const XString& batteryIdentifier);

            virtual void setBatteryType(const XString& batteryType);
            virtual void setBatteryIdentifier(const XString& batteryIdentifier);
            virtual void setBatteryVoltageLevel(XNumber batteryVoltageLevel);

            std::shared_ptr<XIpmiBattery> imp_;

        protected:
            XIpmiBattery();
        };

        using XArrayOfXIpmiBattery = std::vector<XIpmiBattery>;
    }
}
        