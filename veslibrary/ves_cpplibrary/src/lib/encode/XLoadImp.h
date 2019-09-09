#pragma once
        
#include "XLoad.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XLoadImp : public XLoad, public XJsonable
        {
        public:
            XLoadImp();

            virtual json toJson() override;

            virtual void setShortTerm(XNumber shortTerm) override;
            virtual void setLongTerm(XNumber longTerm) override;
            virtual void setMidTerm(XNumber midTerm) override;

        private:
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        