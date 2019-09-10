#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiHsbp 
        {
        public:
            XIpmiHsbp(const XString& hsbpIdentifier);

            virtual void setHsbpTemperature(XNumber hsbpTemperature);
            virtual void setHsbpIdentifier(const XString& hsbpIdentifier);

            std::shared_ptr<XIpmiHsbp> imp_;

        protected:
            XIpmiHsbp();
        };

        using XArrayOfXIpmiHsbp = std::vector<XIpmiHsbp>;
    }
}
        