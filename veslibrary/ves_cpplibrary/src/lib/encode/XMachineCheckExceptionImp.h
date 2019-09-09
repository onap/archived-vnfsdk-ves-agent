#pragma once
        
#include "XMachineCheckException.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XMachineCheckExceptionImp : public XMachineCheckException, public XJsonable
        {
        public:
            XMachineCheckExceptionImp(const XString& vmIdentifier);

            virtual json toJson() override;

            virtual void setCorrectedMemoryErrors(XNumber correctedMemoryErrors) override;
            virtual void setUncorrectedMemoryErrors(XNumber uncorrectedMemoryErrors) override;
            virtual void setUncorrectedMemoryErrorsIn1Hr(XNumber uncorrectedMemoryErrorsIn1Hr) override;
            virtual void setCorrectedMemoryErrorsIn1Hr(XNumber correctedMemoryErrorsIn1Hr) override;
            virtual void setVmIdentifier(const XString& vmIdentifier) override;
        private:
            //required
            XString vmIdentifier_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        