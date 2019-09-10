#pragma once

#include "XCodecsInUse.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XCodecsInUseImp : public XCodecsInUse, public XJsonable
        {
        public:
            XCodecsInUseImp(const XString& codecIdentifier,
                XInteger numberInUse);

            virtual json toJson() override;
            virtual void setCodecIdentifier(const XString& codecIdentifier) override;
            virtual void setNumberInUse(XInteger numberInUse) override;

        private:
            //required
            XString codecIdentifier_;
            XInteger numberInUse_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        