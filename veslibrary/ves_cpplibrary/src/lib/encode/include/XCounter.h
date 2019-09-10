#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        enum XEnumCounterCriticality
        {
            XEnumCounterCriticalityCRIT,
            XEnumCounterCriticalityMAJ,
        };

        class XCounter 
        {
        public:
            XCounter(XEnumCounterCriticality criticality,
                const XHashMap& hashMap,
                const XString& thresholdCrossed);

            virtual void setThresholdCrossed(const XString& thresholdCrossed);
            virtual void setHashMap(const XHashMap& hashMap);
            virtual void setCriticality(XEnumCounterCriticality criticality);

            std::shared_ptr<XCounter> imp_;

        protected:
            XCounter();
        };

        using XArrayOfXCounter = std::vector<XCounter>;
    }
}
        