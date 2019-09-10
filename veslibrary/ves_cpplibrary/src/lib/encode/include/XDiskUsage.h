#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XDiskUsage 
        {
        public:
            XDiskUsage(const XString& diskIdentifier);

            virtual void setDiskOctetsWriteLast(XNumber diskOctetsWriteLast);
            virtual void setDiskIoTimeAvg(XNumber diskIoTimeAvg);
            virtual void setDiskMergedReadMin(XNumber diskMergedReadMin);
            virtual void setDiskTotalReadLatencyAvg(XNumber diskTotalReadLatencyAvg);
            virtual void setDiskOpsReadMax(XNumber diskOpsReadMax);
            virtual void setDiskOpsReadMin(XNumber diskOpsReadMin);
            virtual void setDiskBusResets(XNumber diskBusResets);
            virtual void setDiskMergedReadLast(XNumber diskMergedReadLast);
            virtual void setDiskTimeReadAvg(XNumber diskTimeReadAvg);
            virtual void setDiskMergedWriteMax(XNumber diskMergedWriteMax);
            virtual void setDiskTime(XNumber diskTime);
            virtual void setDiskOpsWriteLast(XNumber diskOpsWriteLast);
            virtual void setDiskOpsReadAvg(XNumber diskOpsReadAvg);
            virtual void setDiskFlushRequests(XNumber diskFlushRequests);
            virtual void setDiskFlushTime(XNumber diskFlushTime);
            virtual void setDiskOpsReadLast(XNumber diskOpsReadLast);
            virtual void setDiskMergedReadAvg(XNumber diskMergedReadAvg);
            virtual void setDiskWriteCommandsAvg(XNumber diskWriteCommandsAvg);
            virtual void setDiskTimeReadMin(XNumber diskTimeReadMin);
            virtual void setDiskOpsWriteAvg(XNumber diskOpsWriteAvg);
            virtual void setDiskWeightedIoTimeMin(XNumber diskWeightedIoTimeMin);
            virtual void setDiskIoTimeLast(XNumber diskIoTimeLast);
            virtual void setDiskMergedReadMax(XNumber diskMergedReadMax);
            virtual void setDiskOctetsReadMin(XNumber diskOctetsReadMin);
            virtual void setDiskWeightedIoTimeAvg(XNumber diskWeightedIoTimeAvg);
            virtual void setDiskTimeWriteMin(XNumber diskTimeWriteMin);
            virtual void setDiskCommandsAvg(XNumber diskCommandsAvg);
            virtual void setDiskTimeWriteMax(XNumber diskTimeWriteMax);
            virtual void setDiskPendingOperationsMin(XNumber diskPendingOperationsMin);
            virtual void setDiskTimeReadMax(XNumber diskTimeReadMax);
            virtual void setDiskOctetsReadMax(XNumber diskOctetsReadMax);
            virtual void setDiskOpsWriteMin(XNumber diskOpsWriteMin);
            virtual void setDiskReadCommandsAvg(XNumber diskReadCommandsAvg);
            virtual void setDiskMergedWriteMin(XNumber diskMergedWriteMin);
            virtual void setDiskOctetsWriteMax(XNumber diskOctetsWriteMax);
            virtual void setDiskTimeWriteLast(XNumber diskTimeWriteLast);
            virtual void setDiskPendingOperationsLast(XNumber diskPendingOperationsLast);
            virtual void setDiskWeightedIoTimeLast(XNumber diskWeightedIoTimeLast);
            virtual void setDiskIdentifier(const XString& diskIdentifier);
            virtual void setDiskOctetsWriteMin(XNumber diskOctetsWriteMin);
            virtual void setDiskTimeWriteAvg(XNumber diskTimeWriteAvg);
            virtual void setDiskOctetsWriteAvg(XNumber diskOctetsWriteAvg);
            virtual void setDiskOctetsReadLast(XNumber diskOctetsReadLast);
            virtual void setDiskWeightedIoTimeMax(XNumber diskWeightedIoTimeMax);
            virtual void setDiskCommandsAborted(XNumber diskCommandsAborted);
            virtual void setDiskOpsWriteMax(XNumber diskOpsWriteMax);
            virtual void setDiskTimeReadLast(XNumber diskTimeReadLast);
            virtual void setDiskMergedWriteAvg(XNumber diskMergedWriteAvg);
            virtual void setDiskOctetsReadAvg(XNumber diskOctetsReadAvg);
            virtual void setDiskTotalWriteLatencyAvg(XNumber diskTotalWriteLatencyAvg);
            virtual void setDiskIoTimeMax(XNumber diskIoTimeMax);
            virtual void setDiskIoTimeMin(XNumber diskIoTimeMin);
            virtual void setDiskPendingOperationsAvg(XNumber diskPendingOperationsAvg);
            virtual void setDiskMergedWriteLast(XNumber diskMergedWriteLast);
            virtual void setDiskPendingOperationsMax(XNumber diskPendingOperationsMax);

            std::shared_ptr<XDiskUsage> imp_;

        protected:
            XDiskUsage();
        };

        using XArrayOfXDiskUsage = std::vector<XDiskUsage>;
    }
}
        