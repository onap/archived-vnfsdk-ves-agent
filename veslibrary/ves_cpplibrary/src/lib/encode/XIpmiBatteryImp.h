#pragma once
        
#include "XIpmiBattery.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiBatteryImp : public XIpmiBattery, public XJsonable
        {
        public:
            XIpmiBatteryImp(const XString& batteryIdentifier);

            virtual json toJson() override;

            virtual void setBatteryType(const XString& batteryType);
            virtual void setBatteryIdentifier(const XString& batteryIdentifier);
            virtual void setBatteryVoltageLevel(XNumber batteryVoltageLevel);

        private:
            //required
            XString batteryIdentifier_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        