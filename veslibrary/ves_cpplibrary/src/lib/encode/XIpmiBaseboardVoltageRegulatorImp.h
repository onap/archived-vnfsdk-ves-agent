#pragma once
        
#include "XIpmiBaseboardVoltageRegulator.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiBaseboardVoltageRegulatorImp : public XIpmiBaseboardVoltageRegulator, public XJsonable
        {
        public:
            XIpmiBaseboardVoltageRegulatorImp(const XString& baseboardVoltageRegulatorIdentifier);

            virtual json toJson() override;

            virtual void setBaseboardVoltageRegulatorIdentifier(const XString& baseboardVoltageRegulatorIdentifier) override;
            virtual void setVoltageRegulatorTemperature(XNumber voltageRegulatorTemperature) override;

        private:
            //required
            XString baseboardVoltageRegulatorIdentifier_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        