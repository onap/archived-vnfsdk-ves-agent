#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiFan 
        {
        public:
            XIpmiFan(const XString& fanIdentifier);

            virtual void setFanSpeed(XNumber fanSpeed);
            virtual void setFanIdentifier(const XString& fanIdentifier);

            std::shared_ptr<XIpmiFan> imp_;

        protected:
            XIpmiFan();
        };

        using XArrayOfXIpmiFan = std::vector<XIpmiFan>;
    }
}
        