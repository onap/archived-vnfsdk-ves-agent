#pragma once
        
#include "XKey.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XKeyImp : public XKey, public XJsonable
        {
        public:
            XKeyImp(const XString& keyName);

            virtual json toJson() override;

            virtual void setKeyValue(const XString& keyValue) override;
            virtual void setKeyOrder(XInteger keyOrder) override;
            virtual void setKeyName(const XString& keyName) override;

        private:
            //required
            XString keyName_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        