#pragma once
        
#include "XIpmiFan.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiFanImp : public XIpmiFan, public XJsonable
        {
        public:
            XIpmiFanImp(const XString& fanIdentifier);

            virtual json toJson() override;

            virtual void setFanSpeed(XNumber fanSpeed) override;
            virtual void setFanIdentifier(const XString& fanIdentifier) override;

        private:
            //required
            XString fanIdentifier_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        