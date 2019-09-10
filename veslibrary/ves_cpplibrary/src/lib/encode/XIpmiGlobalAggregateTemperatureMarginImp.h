#pragma once
        
#include "XIpmiGlobalAggregateTemperatureMargin.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiGlobalAggregateTemperatureMarginImp : public XIpmiGlobalAggregateTemperatureMargin, public XJsonable
        {
        public:
            XIpmiGlobalAggregateTemperatureMarginImp(const XString& ipmiGlobalAggregateTemperatureMarginIdentifier,
                XNumber globalAggregateTemperatureMargin);

            virtual json toJson() override;

            virtual void setIpmiGlobalAggregateTemperatureMarginIdentifier(const XString& ipmiGlobalAggregateTemperatureMarginIdentifier) override;
            virtual void setGlobalAggregateTemperatureMargin(XNumber globalAggregateTemperatureMargin) override;

        private:
            //required
            XString ipmiGlobalAggregateTemperatureMarginIdentifier_;
            XNumber globalAggregateTemperatureMargin_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        