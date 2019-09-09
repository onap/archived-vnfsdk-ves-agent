#include "XMemoryUsage.h"
#include "XMemoryUsageImp.h"

vagt::encode::XMemoryUsage::XMemoryUsage()
{
}

vagt::encode::XMemoryUsage::XMemoryUsage(const XString & vmIdentifier, XNumber memoryFree, XNumber memoryUsed):
    imp_(make_shared<XMemoryUsageImp>(vmIdentifier, memoryFree, memoryUsed))
{
}

void vagt::encode::XMemoryUsage::setMemorySwapInAvg(XNumber memorySwapInAvg)
{
    return imp_->setMemorySwapInAvg(memorySwapInAvg);
}

void vagt::encode::XMemoryUsage::setMemorySwapUsedAvg(XNumber memorySwapUsedAvg)
{
    return imp_->setMemorySwapUsedAvg(memorySwapUsedAvg);
}

void vagt::encode::XMemoryUsage::setMemorySlabRecl(XNumber memorySlabRecl)
{
    return imp_->setMemorySlabRecl(memorySlabRecl);
}

void vagt::encode::XMemoryUsage::setMemorySwapInRateAvg(XNumber memorySwapInRateAvg)
{
    return imp_->setMemorySwapInRateAvg(memorySwapInRateAvg);
}

void vagt::encode::XMemoryUsage::setMemoryDemand(XNumber memoryDemand)
{
    return imp_->setMemoryDemand(memoryDemand);
}

void vagt::encode::XMemoryUsage::setMemoryConfigured(XNumber memoryConfigured)
{
    return imp_->setMemoryConfigured(memoryConfigured);
}

void vagt::encode::XMemoryUsage::setMemorySharedAvg(XNumber memorySharedAvg)
{
    return imp_->setMemorySharedAvg(memorySharedAvg);
}

void vagt::encode::XMemoryUsage::setVmIdentifier(const XString & vmIdentifier)
{
    return imp_->setVmIdentifier(vmIdentifier);
}

void vagt::encode::XMemoryUsage::setMemoryLatencyAvg(XNumber memoryLatencyAvg)
{
    return imp_->setMemoryLatencyAvg(memoryLatencyAvg);
}

void vagt::encode::XMemoryUsage::setMemorySwapOutAvg(XNumber memorySwapOutAvg)
{
    return imp_->setMemorySwapOutAvg(memorySwapOutAvg);
}

void vagt::encode::XMemoryUsage::setMemorySwapOutRateAvg(XNumber memorySwapOutRateAvg)
{
    return imp_->setMemorySwapOutRateAvg(memorySwapOutRateAvg);
}

void vagt::encode::XMemoryUsage::setMemoryFree(XNumber memoryFree)
{
    return imp_->setMemoryFree(memoryFree);
}

void vagt::encode::XMemoryUsage::setMemorySlabUnrecl(XNumber memorySlabUnrecl)
{
    return imp_->setMemorySlabUnrecl(memorySlabUnrecl);
}

void vagt::encode::XMemoryUsage::setMemoryCached(XNumber memoryCached)
{
    return imp_->setMemoryCached(memoryCached);
}

void vagt::encode::XMemoryUsage::setMemoryUsed(XNumber memoryUsed)
{
    return imp_->setMemoryUsed(memoryUsed);
}

void vagt::encode::XMemoryUsage::setMemoryBuffered(XNumber memoryBuffered)
{
    return imp_->setMemoryBuffered(memoryBuffered);
}

void vagt::encode::XMemoryUsage::setPercentMemoryUsage(XNumber percentMemoryUsage)
{
    return imp_->setPercentMemoryUsage(percentMemoryUsage);
}
