#pragma once

#include "XCounter.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XCounterImp : public XCounter, public XJsonable
        {
        public:
            XCounterImp(XEnumCounterCriticality criticality,
                const XHashMap& hashMap,
                const XString& thresholdCrossed);

            virtual json toJson() override;

            virtual void setThresholdCrossed(const XString& thresholdCrossed) override;
            virtual void setHashMap(const XHashMap& hashMap) override;
            virtual void setCriticality(XEnumCounterCriticality criticality) override;

        private:
            //required
            XString thresholdCrossed_;
            XHashMap hashMap_;
            XEnumCounterCriticality criticality_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}