#include "XDiskUsageImp.h"

XDiskUsageImp::XDiskUsageImp(const XString& diskIdentifier):
        diskIdentifier_(diskIdentifier)
{

}

void XDiskUsageImp::setDiskOctetsWriteLast(XNumber diskOctetsWriteLast)
{
    comVals_["diskOctetsWriteLast"] = diskOctetsWriteLast;
}
            
void XDiskUsageImp::setDiskIoTimeAvg(XNumber diskIoTimeAvg)
{
    comVals_["diskIoTimeAvg"] = diskIoTimeAvg;
}
            
void XDiskUsageImp::setDiskMergedReadMin(XNumber diskMergedReadMin)
{
    comVals_["diskMergedReadMin"] = diskMergedReadMin;
}
            
void XDiskUsageImp::setDiskTotalReadLatencyAvg(XNumber diskTotalReadLatencyAvg)
{
    comVals_["diskTotalReadLatencyAvg"] = diskTotalReadLatencyAvg;
}
            
void XDiskUsageImp::setDiskOpsReadMax(XNumber diskOpsReadMax)
{
    comVals_["diskOpsReadMax"] = diskOpsReadMax;
}
            
void XDiskUsageImp::setDiskOpsReadMin(XNumber diskOpsReadMin)
{
    comVals_["diskOpsReadMin"] = diskOpsReadMin;
}
            
void XDiskUsageImp::setDiskBusResets(XNumber diskBusResets)
{
    comVals_["diskBusResets"] = diskBusResets;
}
            
void XDiskUsageImp::setDiskMergedReadLast(XNumber diskMergedReadLast)
{
    comVals_["diskMergedReadLast"] = diskMergedReadLast;
}
            
void XDiskUsageImp::setDiskTimeReadAvg(XNumber diskTimeReadAvg)
{
    comVals_["diskTimeReadAvg"] = diskTimeReadAvg;
}
            
void XDiskUsageImp::setDiskMergedWriteMax(XNumber diskMergedWriteMax)
{
    comVals_["diskMergedWriteMax"] = diskMergedWriteMax;
}
            
void XDiskUsageImp::setDiskTime(XNumber diskTime)
{
    comVals_["diskTime"] = diskTime;
}
            
void XDiskUsageImp::setDiskOpsWriteLast(XNumber diskOpsWriteLast)
{
    comVals_["diskOpsWriteLast"] = diskOpsWriteLast;
}
            
void XDiskUsageImp::setDiskOpsReadAvg(XNumber diskOpsReadAvg)
{
    comVals_["diskOpsReadAvg"] = diskOpsReadAvg;
}
            
void XDiskUsageImp::setDiskFlushRequests(XNumber diskFlushRequests)
{
    comVals_["diskFlushRequests"] = diskFlushRequests;
}
            
void XDiskUsageImp::setDiskFlushTime(XNumber diskFlushTime)
{
    comVals_["diskFlushTime"] = diskFlushTime;
}
            
void XDiskUsageImp::setDiskOpsReadLast(XNumber diskOpsReadLast)
{
    comVals_["diskOpsReadLast"] = diskOpsReadLast;
}
            
void XDiskUsageImp::setDiskMergedReadAvg(XNumber diskMergedReadAvg)
{
    comVals_["diskMergedReadAvg"] = diskMergedReadAvg;
}
            
void XDiskUsageImp::setDiskWriteCommandsAvg(XNumber diskWriteCommandsAvg)
{
    comVals_["diskWriteCommandsAvg"] = diskWriteCommandsAvg;
}
            
void XDiskUsageImp::setDiskTimeReadMin(XNumber diskTimeReadMin)
{
    comVals_["diskTimeReadMin"] = diskTimeReadMin;
}
            
void XDiskUsageImp::setDiskOpsWriteAvg(XNumber diskOpsWriteAvg)
{
    comVals_["diskOpsWriteAvg"] = diskOpsWriteAvg;
}
            
void XDiskUsageImp::setDiskWeightedIoTimeMin(XNumber diskWeightedIoTimeMin)
{
    comVals_["diskWeightedIoTimeMin"] = diskWeightedIoTimeMin;
}
            
void XDiskUsageImp::setDiskIoTimeLast(XNumber diskIoTimeLast)
{
    comVals_["diskIoTimeLast"] = diskIoTimeLast;
}
            
void XDiskUsageImp::setDiskMergedReadMax(XNumber diskMergedReadMax)
{
    comVals_["diskMergedReadMax"] = diskMergedReadMax;
}
            
void XDiskUsageImp::setDiskOctetsReadMin(XNumber diskOctetsReadMin)
{
    comVals_["diskOctetsReadMin"] = diskOctetsReadMin;
}
            
void XDiskUsageImp::setDiskWeightedIoTimeAvg(XNumber diskWeightedIoTimeAvg)
{
    comVals_["diskWeightedIoTimeAvg"] = diskWeightedIoTimeAvg;
}
            
void XDiskUsageImp::setDiskTimeWriteMin(XNumber diskTimeWriteMin)
{
    comVals_["diskTimeWriteMin"] = diskTimeWriteMin;
}
            
void XDiskUsageImp::setDiskCommandsAvg(XNumber diskCommandsAvg)
{
    comVals_["diskCommandsAvg"] = diskCommandsAvg;
}
            
void XDiskUsageImp::setDiskTimeWriteMax(XNumber diskTimeWriteMax)
{
    comVals_["diskTimeWriteMax"] = diskTimeWriteMax;
}
            
void XDiskUsageImp::setDiskPendingOperationsMin(XNumber diskPendingOperationsMin)
{
    comVals_["diskPendingOperationsMin"] = diskPendingOperationsMin;
}
            
void XDiskUsageImp::setDiskTimeReadMax(XNumber diskTimeReadMax)
{
    comVals_["diskTimeReadMax"] = diskTimeReadMax;
}
            
void XDiskUsageImp::setDiskOctetsReadMax(XNumber diskOctetsReadMax)
{
    comVals_["diskOctetsReadMax"] = diskOctetsReadMax;
}
            
void XDiskUsageImp::setDiskOpsWriteMin(XNumber diskOpsWriteMin)
{
    comVals_["diskOpsWriteMin"] = diskOpsWriteMin;
}
            
void XDiskUsageImp::setDiskReadCommandsAvg(XNumber diskReadCommandsAvg)
{
    comVals_["diskReadCommandsAvg"] = diskReadCommandsAvg;
}
            
void XDiskUsageImp::setDiskMergedWriteMin(XNumber diskMergedWriteMin)
{
    comVals_["diskMergedWriteMin"] = diskMergedWriteMin;
}
            
void XDiskUsageImp::setDiskOctetsWriteMax(XNumber diskOctetsWriteMax)
{
    comVals_["diskOctetsWriteMax"] = diskOctetsWriteMax;
}
            
void XDiskUsageImp::setDiskTimeWriteLast(XNumber diskTimeWriteLast)
{
    comVals_["diskTimeWriteLast"] = diskTimeWriteLast;
}
            
void XDiskUsageImp::setDiskPendingOperationsLast(XNumber diskPendingOperationsLast)
{
    comVals_["diskPendingOperationsLast"] = diskPendingOperationsLast;
}
            
void XDiskUsageImp::setDiskWeightedIoTimeLast(XNumber diskWeightedIoTimeLast)
{
    comVals_["diskWeightedIoTimeLast"] = diskWeightedIoTimeLast;
}
            
void XDiskUsageImp::setDiskIdentifier(const XString& diskIdentifier)
{
    comVals_["diskIdentifier"] = diskIdentifier;
}
            
void XDiskUsageImp::setDiskOctetsWriteMin(XNumber diskOctetsWriteMin)
{
    comVals_["diskOctetsWriteMin"] = diskOctetsWriteMin;
}
            
void XDiskUsageImp::setDiskTimeWriteAvg(XNumber diskTimeWriteAvg)
{
    comVals_["diskTimeWriteAvg"] = diskTimeWriteAvg;
}
            
void XDiskUsageImp::setDiskOctetsWriteAvg(XNumber diskOctetsWriteAvg)
{
    comVals_["diskOctetsWriteAvg"] = diskOctetsWriteAvg;
}
            
void XDiskUsageImp::setDiskOctetsReadLast(XNumber diskOctetsReadLast)
{
    comVals_["diskOctetsReadLast"] = diskOctetsReadLast;
}
            
void XDiskUsageImp::setDiskWeightedIoTimeMax(XNumber diskWeightedIoTimeMax)
{
    comVals_["diskWeightedIoTimeMax"] = diskWeightedIoTimeMax;
}
            
void XDiskUsageImp::setDiskCommandsAborted(XNumber diskCommandsAborted)
{
    comVals_["diskCommandsAborted"] = diskCommandsAborted;
}
            
void XDiskUsageImp::setDiskOpsWriteMax(XNumber diskOpsWriteMax)
{
    comVals_["diskOpsWriteMax"] = diskOpsWriteMax;
}
            
void XDiskUsageImp::setDiskTimeReadLast(XNumber diskTimeReadLast)
{
    comVals_["diskTimeReadLast"] = diskTimeReadLast;
}
            
void XDiskUsageImp::setDiskMergedWriteAvg(XNumber diskMergedWriteAvg)
{
    comVals_["diskMergedWriteAvg"] = diskMergedWriteAvg;
}
            
void XDiskUsageImp::setDiskOctetsReadAvg(XNumber diskOctetsReadAvg)
{
    comVals_["diskOctetsReadAvg"] = diskOctetsReadAvg;
}
            
void XDiskUsageImp::setDiskTotalWriteLatencyAvg(XNumber diskTotalWriteLatencyAvg)
{
    comVals_["diskTotalWriteLatencyAvg"] = diskTotalWriteLatencyAvg;
}
            
void XDiskUsageImp::setDiskIoTimeMax(XNumber diskIoTimeMax)
{
    comVals_["diskIoTimeMax"] = diskIoTimeMax;
}
            
void XDiskUsageImp::setDiskIoTimeMin(XNumber diskIoTimeMin)
{
    comVals_["diskIoTimeMin"] = diskIoTimeMin;
}
            
void XDiskUsageImp::setDiskPendingOperationsAvg(XNumber diskPendingOperationsAvg)
{
    comVals_["diskPendingOperationsAvg"] = diskPendingOperationsAvg;
}
            
void XDiskUsageImp::setDiskMergedWriteLast(XNumber diskMergedWriteLast)
{
    comVals_["diskMergedWriteLast"] = diskMergedWriteLast;
}
            
void XDiskUsageImp::setDiskPendingOperationsMax(XNumber diskPendingOperationsMax)
{
    comVals_["diskPendingOperationsMax"] = diskPendingOperationsMax;
}

json XDiskUsageImp::toJson()
{
    try
    {
        json field = {
            {"diskIdentifier", diskIdentifier_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XDiskUsage to json object:{}.", e.what());
        return json();
    }
}
            