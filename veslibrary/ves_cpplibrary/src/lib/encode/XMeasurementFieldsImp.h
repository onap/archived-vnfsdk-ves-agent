#pragma once

#include "XMeasurementFields.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XMeasurementFieldsImp : public XMeasurementFields, public XJsonable
        {
        public:
            XMeasurementFieldsImp(std::shared_ptr<XCommonEventHeader> header, XNumber measurementInterval);

            virtual std::string toString() override;

            virtual json toJson() override;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() override;

            virtual void setCodecUsageArray(const XArrayOfXCodecsInUse& codecUsageArray) override;
            virtual void setFeatureUsageArray(const XHashMap& featureUsageArray) override;
            virtual void setConfiguredEntities(XInteger configuredEntities) override;
            virtual void setAdditionalMeasurements(const XArrayOfNamedHashMap& additionalMeasurements) override;
            virtual void setCpuUsageArray(const XArrayOfXCpuUsage& cpuUsageArray) override;
            virtual void setRequestRate(XNumber requestRate) override;
            virtual void setFilesystemUsageArray(const XArrayOfXFilesystemUsage& filesystemUsageArray) override;
            virtual void setLoadArray(const XArrayOfXLoad& loadArray) override;
            virtual void setMeasurementInterval(XNumber measurementInterval) override;
            virtual void setMachineCheckExceptionArray(const XArrayOfXMachineCheckException& machineCheckExceptionArray) override;
            virtual void setMeanRequestLatency(XNumber meanRequestLatency) override;
            virtual void setConcurrentSessions(XInteger concurrentSessions) override;
            virtual void setAdditionalFields(const XHashMap& additionalFields) override;
            virtual void setProcessStatsArray(const XArrayOfXProcessStats& processStatsArray) override;
            virtual void setNicPerformanceArray(const XArrayOfXNicPerformance& nicPerformanceArray) override;
            virtual void setDiskUsageArray(const XArrayOfXDiskUsage& diskUsageArray) override;
            virtual void setIpmi(const XIpmi& ipmi) override;
            virtual void setLatencyDistribution(const XArrayOfXLatencyBucketMeasure& latencyDistribution) override;
            virtual void setHugePagesArray(const XArrayOfXHugePages& hugePagesArray) override;
            virtual void setAdditionalObjects(const XArrayOfJsonObject& additionalObjects) override;
            virtual void setMemoryUsageArray(const XArrayOfXMemoryUsage& memoryUsageArray) override;
            virtual void setNumberOfMediaPortsInUse(XInteger numberOfMediaPortsInUse) override;
            virtual void setNfcScalingMetric(XInteger nfcScalingMetric) override;

        private:
            //required
            std::shared_ptr<XCommonEventHeader> header_;
            XEnumMeasurementFieldsMeasurementFieldsVersion measurementFieldsVersion_;
            XNumber measurementInterval_;
            //optional
            XArrayOfXCodecsInUse codecUsageArray_;
            XHashMap featureUsageArray_;
            XArrayOfNamedHashMap additionalMeasurements_;
            XArrayOfXCpuUsage cpuUsageArray_;
            XArrayOfXFilesystemUsage filesystemUsageArray_;
            XArrayOfXLoad loadArray_;
            XArrayOfXMachineCheckException machineCheckExceptionArray_;
            XHashMap additionalFields_;
            XArrayOfXProcessStats processStatsArray_;
            XArrayOfXNicPerformance nicPerformanceArray_;
            XArrayOfXDiskUsage diskUsageArray_;
            XIpmi ipmi_;
            XArrayOfXLatencyBucketMeasure latencyDistribution_;
            XArrayOfXHugePages hugePagesArray_;
            XArrayOfJsonObject additionalObjects_;
            XArrayOfXMemoryUsage memoryUsageArray_;
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        