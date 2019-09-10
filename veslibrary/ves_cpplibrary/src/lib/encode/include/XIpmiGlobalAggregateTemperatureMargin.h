#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiGlobalAggregateTemperatureMargin 
        {
        public:
            XIpmiGlobalAggregateTemperatureMargin(const XString& ipmiGlobalAggregateTemperatureMarginIdentifier,
                XNumber globalAggregateTemperatureMargin);

            virtual void setIpmiGlobalAggregateTemperatureMarginIdentifier(const XString& ipmiGlobalAggregateTemperatureMarginIdentifier);
            virtual void setGlobalAggregateTemperatureMargin(XNumber globalAggregateTemperatureMargin);

            std::shared_ptr<XIpmiGlobalAggregateTemperatureMargin> imp_;

        protected:
            XIpmiGlobalAggregateTemperatureMargin();
        };

        using XArrayOfXIpmiGlobalAggregateTemperatureMargin = std::vector<XIpmiGlobalAggregateTemperatureMargin>;
    }
}
        