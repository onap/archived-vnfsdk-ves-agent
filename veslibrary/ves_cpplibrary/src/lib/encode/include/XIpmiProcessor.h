#pragma once
        
#include "XEvent.h"
#include "XProcessorDimmAggregateThermalMargin.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiProcessor 
        {
        public:
            XIpmiProcessor(const XString& processorIdentifier);

            virtual void setProcessorThermalControlPercent(XNumber processorThermalControlPercent);
            virtual void setProcessorDtsThermalMargin(XNumber processorDtsThermalMargin);
            virtual void setProcessorIdentifier(const XString& processorIdentifier);
            virtual void setProcessorDimmAggregateThermalMarginArray(const XArrayOfXProcessorDimmAggregateThermalMargin& processorDimmAggregateThermalMarginArray);

            std::shared_ptr<XIpmiProcessor> imp_;

        protected:
            XIpmiProcessor();
        };

        using XArrayOfXIpmiProcessor = std::vector<XIpmiProcessor>;
    }
}
        