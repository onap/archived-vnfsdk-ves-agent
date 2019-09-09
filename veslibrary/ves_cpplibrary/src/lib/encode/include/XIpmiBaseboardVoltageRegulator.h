#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiBaseboardVoltageRegulator 
        {
        public:
            XIpmiBaseboardVoltageRegulator(const XString& baseboardVoltageRegulatorIdentifier);

            virtual void setBaseboardVoltageRegulatorIdentifier(const XString& baseboardVoltageRegulatorIdentifier);
            virtual void setVoltageRegulatorTemperature(XNumber voltageRegulatorTemperature);

            std::shared_ptr<XIpmiBaseboardVoltageRegulator> imp_;

        protected:
            XIpmiBaseboardVoltageRegulator();
        };

        using XArrayOfXIpmiBaseboardVoltageRegulator = std::vector<XIpmiBaseboardVoltageRegulator>;
    }
}
        