#pragma once

#include "XIpmiNic.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiNicImp : public XIpmiNic, public XJsonable
        {
        public:
            XIpmiNicImp(const XString& nicIdentifier);

            virtual json toJson() override;

            virtual void setNicIdentifier(const XString& nicIdentifier) override;
            virtual void setNicTemperature(XNumber nicTemperature) override;

        private:
            //required
            XString nicIdentifier_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        