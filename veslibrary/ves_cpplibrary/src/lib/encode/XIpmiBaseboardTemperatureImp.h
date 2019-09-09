#pragma once
        
#include "XIpmiBaseboardTemperature.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiBaseboardTemperatureImp : public XIpmiBaseboardTemperature, public XJsonable
        {
        public:
            XIpmiBaseboardTemperatureImp(const XString& baseboardTemperatureIdentifier);

            virtual json toJson() override;

            virtual void setBaseboardTemperature(XNumber baseboardTemperature) override;
            virtual void setBaseboardTemperatureIdentifier(const XString& baseboardTemperatureIdentifier) override;

        private:
            //required
            XString baseboardTemperatureIdentifier_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        