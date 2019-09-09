#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XLoad 
        {
        public:
            XLoad();

            virtual void setShortTerm(XNumber shortTerm);
            virtual void setLongTerm(XNumber longTerm);
            virtual void setMidTerm(XNumber midTerm);

            std::shared_ptr<XLoad> imp_;
        protected:
            XLoad(void*);
        };

        using XArrayOfXLoad = std::vector<XLoad>;
    }
}
        