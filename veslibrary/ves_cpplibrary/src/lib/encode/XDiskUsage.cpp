#include "XDiskUsage.h"
#include "XDiskUsageImp.h"

vagt::encode::XDiskUsage::XDiskUsage()
{
}

vagt::encode::XDiskUsage::XDiskUsage(const XString & diskIdentifier):
    imp_(make_shared<XDiskUsageImp>(diskIdentifier))
{
}

void vagt::encode::XDiskUsage::setDiskOctetsWriteLast(XNumber diskOctetsWriteLast)
{
    return imp_->setDiskOctetsWriteLast(diskOctetsWriteLast);
}

void vagt::encode::XDiskUsage::setDiskIoTimeAvg(XNumber diskIoTimeAvg)
{
    return imp_->setDiskIoTimeAvg(diskIoTimeAvg);
}

void vagt::encode::XDiskUsage::setDiskMergedReadMin(XNumber diskMergedReadMin)
{
    return imp_->setDiskMergedReadMin(diskMergedReadMin);
}

void vagt::encode::XDiskUsage::setDiskTotalReadLatencyAvg(XNumber diskTotalReadLatencyAvg)
{
    return imp_->setDiskTotalReadLatencyAvg(diskTotalReadLatencyAvg);
}

void vagt::encode::XDiskUsage::setDiskOpsReadMax(XNumber diskOpsReadMax)
{
    return imp_->setDiskOpsReadMax(diskOpsReadMax);
}

void vagt::encode::XDiskUsage::setDiskOpsReadMin(XNumber diskOpsReadMin)
{
    return imp_->setDiskOpsReadMin(diskOpsReadMin);
}

void vagt::encode::XDiskUsage::setDiskBusResets(XNumber diskBusResets)
{
    return imp_->setDiskBusResets(diskBusResets);
}

void vagt::encode::XDiskUsage::setDiskMergedReadLast(XNumber diskMergedReadLast)
{
    return imp_->setDiskMergedReadLast(diskMergedReadLast);
}

void vagt::encode::XDiskUsage::setDiskTimeReadAvg(XNumber diskTimeReadAvg)
{
    return imp_->setDiskTimeReadAvg(diskTimeReadAvg);
}

void vagt::encode::XDiskUsage::setDiskMergedWriteMax(XNumber diskMergedWriteMax)
{
    return imp_->setDiskMergedWriteMax(diskMergedWriteMax);
}

void vagt::encode::XDiskUsage::setDiskTime(XNumber diskTime)
{
    return imp_->setDiskTime(diskTime);
}

void vagt::encode::XDiskUsage::setDiskOpsWriteLast(XNumber diskOpsWriteLast)
{
    return imp_->setDiskOpsWriteLast(diskOpsWriteLast);
}

void vagt::encode::XDiskUsage::setDiskOpsReadAvg(XNumber diskOpsReadAvg)
{
    return imp_->setDiskOpsReadAvg(diskOpsReadAvg);
}

void vagt::encode::XDiskUsage::setDiskFlushRequests(XNumber diskFlushRequests)
{
    return imp_->setDiskFlushRequests(diskFlushRequests);
}

void vagt::encode::XDiskUsage::setDiskFlushTime(XNumber diskFlushTime)
{
    return imp_->setDiskFlushTime(diskFlushTime);
}

void vagt::encode::XDiskUsage::setDiskOpsReadLast(XNumber diskOpsReadLast)
{
    return imp_->setDiskOpsReadLast(diskOpsReadLast);
}

void vagt::encode::XDiskUsage::setDiskMergedReadAvg(XNumber diskMergedReadAvg)
{
    return imp_->setDiskMergedReadAvg(diskMergedReadAvg);
}

void vagt::encode::XDiskUsage::setDiskWriteCommandsAvg(XNumber diskWriteCommandsAvg)
{
    return imp_->setDiskWriteCommandsAvg(diskWriteCommandsAvg);
}

void vagt::encode::XDiskUsage::setDiskTimeReadMin(XNumber diskTimeReadMin)
{
    return imp_->setDiskTimeReadMin(diskTimeReadMin);
}

void vagt::encode::XDiskUsage::setDiskOpsWriteAvg(XNumber diskOpsWriteAvg)
{
    return imp_->setDiskOpsWriteAvg(diskOpsWriteAvg);
}

void vagt::encode::XDiskUsage::setDiskWeightedIoTimeMin(XNumber diskWeightedIoTimeMin)
{
    return imp_->setDiskWeightedIoTimeMin(diskWeightedIoTimeMin);
}

void vagt::encode::XDiskUsage::setDiskIoTimeLast(XNumber diskIoTimeLast)
{
    return imp_->setDiskIoTimeLast(diskIoTimeLast);
}

void vagt::encode::XDiskUsage::setDiskMergedReadMax(XNumber diskMergedReadMax)
{
    return imp_->setDiskMergedReadMax(diskMergedReadMax);
}

void vagt::encode::XDiskUsage::setDiskOctetsReadMin(XNumber diskOctetsReadMin)
{
    return imp_->setDiskOctetsReadMin(diskOctetsReadMin);
}

void vagt::encode::XDiskUsage::setDiskWeightedIoTimeAvg(XNumber diskWeightedIoTimeAvg)
{
    return imp_->setDiskWeightedIoTimeAvg(diskWeightedIoTimeAvg);
}

void vagt::encode::XDiskUsage::setDiskTimeWriteMin(XNumber diskTimeWriteMin)
{
    return imp_->setDiskTimeWriteMin(diskTimeWriteMin);
}

void vagt::encode::XDiskUsage::setDiskCommandsAvg(XNumber diskCommandsAvg)
{
    return imp_->setDiskCommandsAvg(diskCommandsAvg);
}

void vagt::encode::XDiskUsage::setDiskTimeWriteMax(XNumber diskTimeWriteMax)
{
    return imp_->setDiskTimeWriteMax(diskTimeWriteMax);
}

void vagt::encode::XDiskUsage::setDiskPendingOperationsMin(XNumber diskPendingOperationsMin)
{
    return imp_->setDiskPendingOperationsMin(diskPendingOperationsMin);
}

void vagt::encode::XDiskUsage::setDiskTimeReadMax(XNumber diskTimeReadMax)
{
    return imp_->setDiskTimeReadMax(diskTimeReadMax);
}

void vagt::encode::XDiskUsage::setDiskOctetsReadMax(XNumber diskOctetsReadMax)
{
    return imp_->setDiskOctetsReadMax(diskOctetsReadMax);
}

void vagt::encode::XDiskUsage::setDiskOpsWriteMin(XNumber diskOpsWriteMin)
{
    return imp_->setDiskOpsWriteMin(diskOpsWriteMin);
}

void vagt::encode::XDiskUsage::setDiskReadCommandsAvg(XNumber diskReadCommandsAvg)
{
    return imp_->setDiskReadCommandsAvg(diskReadCommandsAvg);
}

void vagt::encode::XDiskUsage::setDiskMergedWriteMin(XNumber diskMergedWriteMin)
{
    return imp_->setDiskMergedWriteMin(diskMergedWriteMin);
}

void vagt::encode::XDiskUsage::setDiskOctetsWriteMax(XNumber diskOctetsWriteMax)
{
    return imp_->setDiskOctetsWriteMax(diskOctetsWriteMax);
}

void vagt::encode::XDiskUsage::setDiskTimeWriteLast(XNumber diskTimeWriteLast)
{
    return imp_->setDiskTimeWriteLast(diskTimeWriteLast);
}

void vagt::encode::XDiskUsage::setDiskPendingOperationsLast(XNumber diskPendingOperationsLast)
{
    return imp_->setDiskPendingOperationsLast(diskPendingOperationsLast);
}

void vagt::encode::XDiskUsage::setDiskWeightedIoTimeLast(XNumber diskWeightedIoTimeLast)
{
    return imp_->setDiskWeightedIoTimeLast(diskWeightedIoTimeLast);
}

void vagt::encode::XDiskUsage::setDiskIdentifier(const XString & diskIdentifier)
{
    return imp_->setDiskIdentifier(diskIdentifier);
}

void vagt::encode::XDiskUsage::setDiskOctetsWriteMin(XNumber diskOctetsWriteMin)
{
    return imp_->setDiskOctetsWriteMin(diskOctetsWriteMin);
}

void vagt::encode::XDiskUsage::setDiskTimeWriteAvg(XNumber diskTimeWriteAvg)
{
    return imp_->setDiskTimeWriteAvg(diskTimeWriteAvg);
}

void vagt::encode::XDiskUsage::setDiskOctetsWriteAvg(XNumber diskOctetsWriteAvg)
{
    return imp_->setDiskOctetsWriteAvg(diskOctetsWriteAvg);
}

void vagt::encode::XDiskUsage::setDiskOctetsReadLast(XNumber diskOctetsReadLast)
{
    return imp_->setDiskOctetsReadLast(diskOctetsReadLast);
}

void vagt::encode::XDiskUsage::setDiskWeightedIoTimeMax(XNumber diskWeightedIoTimeMax)
{
    return imp_->setDiskWeightedIoTimeMax(diskWeightedIoTimeMax);
}

void vagt::encode::XDiskUsage::setDiskCommandsAborted(XNumber diskCommandsAborted)
{
    return imp_->setDiskCommandsAborted(diskCommandsAborted);
}

void vagt::encode::XDiskUsage::setDiskOpsWriteMax(XNumber diskOpsWriteMax)
{
    return imp_->setDiskOpsWriteMax(diskOpsWriteMax);
}

void vagt::encode::XDiskUsage::setDiskTimeReadLast(XNumber diskTimeReadLast)
{
    return imp_->setDiskTimeReadLast(diskTimeReadLast);
}

void vagt::encode::XDiskUsage::setDiskMergedWriteAvg(XNumber diskMergedWriteAvg)
{
    return imp_->setDiskMergedWriteAvg(diskMergedWriteAvg);
}

void vagt::encode::XDiskUsage::setDiskOctetsReadAvg(XNumber diskOctetsReadAvg)
{
    return imp_->setDiskOctetsReadAvg(diskOctetsReadAvg);
}

void vagt::encode::XDiskUsage::setDiskTotalWriteLatencyAvg(XNumber diskTotalWriteLatencyAvg)
{
    return imp_->setDiskTotalWriteLatencyAvg(diskTotalWriteLatencyAvg);
}

void vagt::encode::XDiskUsage::setDiskIoTimeMax(XNumber diskIoTimeMax)
{
    return imp_->setDiskIoTimeMax(diskIoTimeMax);
}

void vagt::encode::XDiskUsage::setDiskIoTimeMin(XNumber diskIoTimeMin)
{
    return imp_->setDiskIoTimeMin(diskIoTimeMin);
}

void vagt::encode::XDiskUsage::setDiskPendingOperationsAvg(XNumber diskPendingOperationsAvg)
{
    return imp_->setDiskPendingOperationsAvg(diskPendingOperationsAvg);
}

void vagt::encode::XDiskUsage::setDiskMergedWriteLast(XNumber diskMergedWriteLast)
{
    return imp_->setDiskMergedWriteLast(diskMergedWriteLast);
}

void vagt::encode::XDiskUsage::setDiskPendingOperationsMax(XNumber diskPendingOperationsMax)
{
    return imp_->setDiskPendingOperationsMax(diskPendingOperationsMax);
}
