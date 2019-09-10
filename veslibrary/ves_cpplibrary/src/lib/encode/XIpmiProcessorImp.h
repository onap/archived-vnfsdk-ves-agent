#pragma once
        
#include "XIpmiProcessor.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiProcessorImp : public XIpmiProcessor, public XJsonable
        {
        public:
            XIpmiProcessorImp(const XString& processorIdentifier);

            virtual json toJson() override;

            virtual void setProcessorThermalControlPercent(XNumber processorThermalControlPercent) override;
            virtual void setProcessorDtsThermalMargin(XNumber processorDtsThermalMargin) override;
            virtual void setProcessorIdentifier(const XString& processorIdentifier) override;
            virtual void setProcessorDimmAggregateThermalMarginArray(const XArrayOfXProcessorDimmAggregateThermalMargin& processorDimmAggregateThermalMarginArray) override;

        private:
            //required
            XString processorIdentifier_;
            //optional
            XArrayOfXProcessorDimmAggregateThermalMargin processorDimmAggregateThermalMarginArray_;
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        