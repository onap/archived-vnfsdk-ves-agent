#pragma once
        
#include "XDiskUsage.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XDiskUsageImp : public XDiskUsage, public XJsonable
        {
        public:
            XDiskUsageImp(const XString& diskIdentifier);

            virtual json toJson() override;

            virtual void setDiskOctetsWriteLast(XNumber diskOctetsWriteLast) override;
            virtual void setDiskIoTimeAvg(XNumber diskIoTimeAvg) override;
            virtual void setDiskMergedReadMin(XNumber diskMergedReadMin) override;
            virtual void setDiskTotalReadLatencyAvg(XNumber diskTotalReadLatencyAvg) override;
            virtual void setDiskOpsReadMax(XNumber diskOpsReadMax) override;
            virtual void setDiskOpsReadMin(XNumber diskOpsReadMin) override;
            virtual void setDiskBusResets(XNumber diskBusResets) override;
            virtual void setDiskMergedReadLast(XNumber diskMergedReadLast) override;
            virtual void setDiskTimeReadAvg(XNumber diskTimeReadAvg) override;
            virtual void setDiskMergedWriteMax(XNumber diskMergedWriteMax) override;
            virtual void setDiskTime(XNumber diskTime) override;
            virtual void setDiskOpsWriteLast(XNumber diskOpsWriteLast) override;
            virtual void setDiskOpsReadAvg(XNumber diskOpsReadAvg) override;
            virtual void setDiskFlushRequests(XNumber diskFlushRequests) override;
            virtual void setDiskFlushTime(XNumber diskFlushTime) override;
            virtual void setDiskOpsReadLast(XNumber diskOpsReadLast) override;
            virtual void setDiskMergedReadAvg(XNumber diskMergedReadAvg) override;
            virtual void setDiskWriteCommandsAvg(XNumber diskWriteCommandsAvg) override;
            virtual void setDiskTimeReadMin(XNumber diskTimeReadMin) override;
            virtual void setDiskOpsWriteAvg(XNumber diskOpsWriteAvg) override;
            virtual void setDiskWeightedIoTimeMin(XNumber diskWeightedIoTimeMin) override;
            virtual void setDiskIoTimeLast(XNumber diskIoTimeLast) override;
            virtual void setDiskMergedReadMax(XNumber diskMergedReadMax) override;
            virtual void setDiskOctetsReadMin(XNumber diskOctetsReadMin) override;
            virtual void setDiskWeightedIoTimeAvg(XNumber diskWeightedIoTimeAvg) override;
            virtual void setDiskTimeWriteMin(XNumber diskTimeWriteMin) override;
            virtual void setDiskCommandsAvg(XNumber diskCommandsAvg) override;
            virtual void setDiskTimeWriteMax(XNumber diskTimeWriteMax) override;
            virtual void setDiskPendingOperationsMin(XNumber diskPendingOperationsMin) override;
            virtual void setDiskTimeReadMax(XNumber diskTimeReadMax) override;
            virtual void setDiskOctetsReadMax(XNumber diskOctetsReadMax) override;
            virtual void setDiskOpsWriteMin(XNumber diskOpsWriteMin) override;
            virtual void setDiskReadCommandsAvg(XNumber diskReadCommandsAvg) override;
            virtual void setDiskMergedWriteMin(XNumber diskMergedWriteMin) override;
            virtual void setDiskOctetsWriteMax(XNumber diskOctetsWriteMax) override;
            virtual void setDiskTimeWriteLast(XNumber diskTimeWriteLast) override;
            virtual void setDiskPendingOperationsLast(XNumber diskPendingOperationsLast) override;
            virtual void setDiskWeightedIoTimeLast(XNumber diskWeightedIoTimeLast) override;
            virtual void setDiskIdentifier(const XString& diskIdentifier) override;
            virtual void setDiskOctetsWriteMin(XNumber diskOctetsWriteMin) override;
            virtual void setDiskTimeWriteAvg(XNumber diskTimeWriteAvg) override;
            virtual void setDiskOctetsWriteAvg(XNumber diskOctetsWriteAvg) override;
            virtual void setDiskOctetsReadLast(XNumber diskOctetsReadLast) override;
            virtual void setDiskWeightedIoTimeMax(XNumber diskWeightedIoTimeMax) override;
            virtual void setDiskCommandsAborted(XNumber diskCommandsAborted) override;
            virtual void setDiskOpsWriteMax(XNumber diskOpsWriteMax) override;
            virtual void setDiskTimeReadLast(XNumber diskTimeReadLast) override;
            virtual void setDiskMergedWriteAvg(XNumber diskMergedWriteAvg) override;
            virtual void setDiskOctetsReadAvg(XNumber diskOctetsReadAvg) override;
            virtual void setDiskTotalWriteLatencyAvg(XNumber diskTotalWriteLatencyAvg) override;
            virtual void setDiskIoTimeMax(XNumber diskIoTimeMax) override;
            virtual void setDiskIoTimeMin(XNumber diskIoTimeMin) override;
            virtual void setDiskPendingOperationsAvg(XNumber diskPendingOperationsAvg) override;
            virtual void setDiskMergedWriteLast(XNumber diskMergedWriteLast) override;
            virtual void setDiskPendingOperationsMax(XNumber diskPendingOperationsMax) override;

        private:
            //required
            XString diskIdentifier_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        