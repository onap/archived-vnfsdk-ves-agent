#include "XMachineCheckExceptionImp.h"

XMachineCheckExceptionImp::XMachineCheckExceptionImp(const XString& vmIdentifier):
        vmIdentifier_(vmIdentifier)
{

}

void XMachineCheckExceptionImp::setCorrectedMemoryErrors(XNumber correctedMemoryErrors)
{
    comVals_["correctedMemoryErrors"] = correctedMemoryErrors;
}
            
void XMachineCheckExceptionImp::setUncorrectedMemoryErrors(XNumber uncorrectedMemoryErrors)
{
    comVals_["uncorrectedMemoryErrors"] = uncorrectedMemoryErrors;
}
            
void XMachineCheckExceptionImp::setUncorrectedMemoryErrorsIn1Hr(XNumber uncorrectedMemoryErrorsIn1Hr)
{
    comVals_["uncorrectedMemoryErrorsIn1Hr"] = uncorrectedMemoryErrorsIn1Hr;
}
            
void XMachineCheckExceptionImp::setCorrectedMemoryErrorsIn1Hr(XNumber correctedMemoryErrorsIn1Hr)
{
    comVals_["correctedMemoryErrorsIn1Hr"] = correctedMemoryErrorsIn1Hr;
}
            
void XMachineCheckExceptionImp::setVmIdentifier(const XString& vmIdentifier)
{
    comVals_["vmIdentifier"] = vmIdentifier;
}

json XMachineCheckExceptionImp::toJson()
{
    try
    {
        json field = {
            {"vmIdentifier", vmIdentifier_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XMachineCheckException to json object:{}.", e.what());
        return json();
    }
}
            