#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XKey 
        {
        public:
            XKey(const XString& keyName);

            virtual void setKeyValue(const XString& keyValue);
            virtual void setKeyOrder(XInteger keyOrder);
            virtual void setKeyName(const XString& keyName);

            std::shared_ptr<XKey> imp_;

        protected:
            XKey();
        };

        using XArrayOfXKey = std::vector<XKey>;
    }
}
        