#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XProcessorDimmAggregateThermalMargin 
        {
        public:
            XProcessorDimmAggregateThermalMargin(const XString& processorDimmAggregateThermalMarginIdentifier,
                XNumber thermalMargin);

            virtual void setProcessorDimmAggregateThermalMarginIdentifier(const XString& processorDimmAggregateThermalMarginIdentifier);
            virtual void setThermalMargin(XNumber thermalMargin);

            std::shared_ptr<XProcessorDimmAggregateThermalMargin> imp_;

        protected:
            XProcessorDimmAggregateThermalMargin();
        };

        using XArrayOfXProcessorDimmAggregateThermalMargin = std::vector<XProcessorDimmAggregateThermalMargin>;
    }
}
        