#include "XCpuUsage.h"
#include "XCpuUsageImp.h"

vagt::encode::XCpuUsage::XCpuUsage()
{
}

vagt::encode::XCpuUsage::XCpuUsage(const XString & cpuIdentifier, XNumber percentUsage):
    imp_(make_shared<XCpuUsageImp>(cpuIdentifier, percentUsage))
{
}

void vagt::encode::XCpuUsage::setPercentUsage(XNumber percentUsage)
{
    return imp_->setPercentUsage(percentUsage);
}

void vagt::encode::XCpuUsage::setCpuUsageInterrupt(XNumber cpuUsageInterrupt)
{
    return imp_->setCpuUsageInterrupt(cpuUsageInterrupt);
}

void vagt::encode::XCpuUsage::setCpuWait(XNumber cpuWait)
{
    return imp_->setCpuWait(cpuWait);
}

void vagt::encode::XCpuUsage::setCpuCapacityContention(XNumber cpuCapacityContention)
{
    return imp_->setCpuCapacityContention(cpuCapacityContention);
}

void vagt::encode::XCpuUsage::setCpuUsageNice(XNumber cpuUsageNice)
{
    return imp_->setCpuUsageNice(cpuUsageNice);
}

void vagt::encode::XCpuUsage::setCpuDemandMhz(XNumber cpuDemandMhz)
{
    return imp_->setCpuDemandMhz(cpuDemandMhz);
}

void vagt::encode::XCpuUsage::setCpuUsageSoftIrq(XNumber cpuUsageSoftIrq)
{
    return imp_->setCpuUsageSoftIrq(cpuUsageSoftIrq);
}

void vagt::encode::XCpuUsage::setCpuLatencyAvg(XNumber cpuLatencyAvg)
{
    return imp_->setCpuLatencyAvg(cpuLatencyAvg);
}

void vagt::encode::XCpuUsage::setCpuUsageSteal(XNumber cpuUsageSteal)
{
    return imp_->setCpuUsageSteal(cpuUsageSteal);
}

void vagt::encode::XCpuUsage::setCpuDemandPct(XNumber cpuDemandPct)
{
    return imp_->setCpuDemandPct(cpuDemandPct);
}

void vagt::encode::XCpuUsage::setCpuDemandAvg(XNumber cpuDemandAvg)
{
    return imp_->setCpuDemandAvg(cpuDemandAvg);
}

void vagt::encode::XCpuUsage::setCpuIdle(XNumber cpuIdle)
{
    return imp_->setCpuIdle(cpuIdle);
}

void vagt::encode::XCpuUsage::setCpuSwapWaitTime(XNumber cpuSwapWaitTime)
{
    return imp_->setCpuSwapWaitTime(cpuSwapWaitTime);
}

void vagt::encode::XCpuUsage::setCpuUsageSystem(XNumber cpuUsageSystem)
{
    return imp_->setCpuUsageSystem(cpuUsageSystem);
}

void vagt::encode::XCpuUsage::setCpuOverheadAvg(XNumber cpuOverheadAvg)
{
    return imp_->setCpuOverheadAvg(cpuOverheadAvg);
}

void vagt::encode::XCpuUsage::setCpuUsageUser(XNumber cpuUsageUser)
{
    return imp_->setCpuUsageUser(cpuUsageUser);
}

void vagt::encode::XCpuUsage::setCpuIdentifier(const XString & cpuIdentifier)
{
    return imp_->setCpuIdentifier(cpuIdentifier);
}
