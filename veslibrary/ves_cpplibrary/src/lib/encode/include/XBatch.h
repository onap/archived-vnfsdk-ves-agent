#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XBatch: public XSerialable
        {
        public:
            virtual std::string toString() = 0;

            virtual void addEvent(std::shared_ptr<vagt::encode::XSerialable> event) = 0;

            static std::shared_ptr<XBatch> create();
        };
    }
}
        