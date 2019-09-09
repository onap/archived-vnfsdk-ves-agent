#include "XMachineCheckException.h"
#include "XMachineCheckExceptionImp.h"

vagt::encode::XMachineCheckException::XMachineCheckException()
{
}

vagt::encode::XMachineCheckException::XMachineCheckException(const XString & vmIdentifier):
    imp_(make_shared<XMachineCheckExceptionImp>(vmIdentifier))
{
}

void vagt::encode::XMachineCheckException::setCorrectedMemoryErrors(XNumber correctedMemoryErrors)
{
    return imp_->setCorrectedMemoryErrors(correctedMemoryErrors);
}

void vagt::encode::XMachineCheckException::setUncorrectedMemoryErrors(XNumber uncorrectedMemoryErrors)
{
    return imp_->setUncorrectedMemoryErrors(uncorrectedMemoryErrors);
}

void vagt::encode::XMachineCheckException::setUncorrectedMemoryErrorsIn1Hr(XNumber uncorrectedMemoryErrorsIn1Hr)
{
    return imp_->setUncorrectedMemoryErrorsIn1Hr(uncorrectedMemoryErrorsIn1Hr);
}

void vagt::encode::XMachineCheckException::setCorrectedMemoryErrorsIn1Hr(XNumber correctedMemoryErrorsIn1Hr)
{
    return imp_->setCorrectedMemoryErrorsIn1Hr(correctedMemoryErrorsIn1Hr);
}

void vagt::encode::XMachineCheckException::setVmIdentifier(const XString & vmIdentifier)
{
    return imp_->setVmIdentifier(vmIdentifier);
}
