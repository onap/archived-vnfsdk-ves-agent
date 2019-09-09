#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XIpmiNic 
        {
        public:
            XIpmiNic(const XString& nicIdentifier);

            virtual void setNicIdentifier(const XString& nicIdentifier);
            virtual void setNicTemperature(XNumber nicTemperature);

            std::shared_ptr<XIpmiNic> imp_;

        protected:
            XIpmiNic();
        };
        
        using XArrayOfXIpmiNic = std::vector<XIpmiNic>;
    }
}
        