#pragma once
        
#include "XIpmiHsbp.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiHsbpImp : public XIpmiHsbp, public XJsonable
        {
        public:
            XIpmiHsbpImp(const XString& hsbpIdentifier);

            virtual json toJson() override;

            virtual void setHsbpTemperature(XNumber hsbpTemperature) override;
            virtual void setHsbpIdentifier(const XString& hsbpIdentifier) override;

        private:
            //required
            XString hsbpIdentifier_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        