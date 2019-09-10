#pragma once
        
#include "XProcessorDimmAggregateThermalMargin.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XProcessorDimmAggregateThermalMarginImp : public XProcessorDimmAggregateThermalMargin, public XJsonable
        {
        public:
            XProcessorDimmAggregateThermalMarginImp(const XString& processorDimmAggregateThermalMarginIdentifier,
                XNumber thermalMargin);

            virtual json toJson() override;

            virtual void setProcessorDimmAggregateThermalMarginIdentifier(const XString& processorDimmAggregateThermalMarginIdentifier);
            virtual void setThermalMargin(XNumber thermalMargin);

        private:
            //required
            XString processorDimmAggregateThermalMarginIdentifier_;
            XNumber thermalMargin_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        