#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiBaseboardTemperature 
        {
        public:
            XIpmiBaseboardTemperature(const XString& baseboardTemperatureIdentifier);

            virtual void setBaseboardTemperature(XNumber baseboardTemperature);
            virtual void setBaseboardTemperatureIdentifier(const XString& baseboardTemperatureIdentifier);

            std::shared_ptr<XIpmiBaseboardTemperature> imp_;

        protected:
            XIpmiBaseboardTemperature();
        };

        using XArrayOfXIpmiBaseboardTemperature = std::vector<XIpmiBaseboardTemperature>;
    }
}
        