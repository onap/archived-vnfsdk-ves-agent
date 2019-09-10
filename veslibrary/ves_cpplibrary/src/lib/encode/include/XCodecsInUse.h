#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XCodecsInUse 
        {
        public:
            XCodecsInUse(const XString& codecIdentifier,
                XInteger numberInUse);

            virtual void setCodecIdentifier(const XString& codecIdentifier);
            virtual void setNumberInUse(XInteger numberInUse);

            std::shared_ptr<XCodecsInUse> imp_;
        protected:
            XCodecsInUse();
        };

        using XArrayOfXCodecsInUse = std::vector<XCodecsInUse>;
    }
}
        