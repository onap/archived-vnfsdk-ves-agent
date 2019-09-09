#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XMachineCheckException 
        {
        public:
            XMachineCheckException(const XString& vmIdentifier);

            virtual void setCorrectedMemoryErrors(XNumber correctedMemoryErrors);
            virtual void setUncorrectedMemoryErrors(XNumber uncorrectedMemoryErrors);
            virtual void setUncorrectedMemoryErrorsIn1Hr(XNumber uncorrectedMemoryErrorsIn1Hr);
            virtual void setCorrectedMemoryErrorsIn1Hr(XNumber correctedMemoryErrorsIn1Hr);
            virtual void setVmIdentifier(const XString& vmIdentifier);

            std::shared_ptr<XMachineCheckException> imp_;

        protected:
            XMachineCheckException();
        };

        using XArrayOfXMachineCheckException = std::vector<XMachineCheckException>;
    }
}
        