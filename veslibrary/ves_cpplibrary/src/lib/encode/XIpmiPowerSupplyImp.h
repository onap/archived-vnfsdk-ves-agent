#pragma once
        
#include "XIpmiPowerSupply.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiPowerSupplyImp : public XIpmiPowerSupply, public XJsonable
        {
        public:
            XIpmiPowerSupplyImp(const XString& powerSupplyIdentifier);

            virtual json toJson() override;

            virtual void setPowerSupplyInputPower(XNumber powerSupplyInputPower) override;
            virtual void setPowerSupplyCurrentOutputPercent(XNumber powerSupplyCurrentOutputPercent) override;
            virtual void setPowerSupplyIdentifier(const XString& powerSupplyIdentifier) override;
            virtual void setPowerSupplyTemperature(XNumber powerSupplyTemperature) override;

        private:
            //required
            XString powerSupplyIdentifier_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        