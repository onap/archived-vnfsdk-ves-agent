#pragma once
        
#include "XCommonEventHeader.h"
#include "XNamedHashMap.h"
#include "XCodecsInUse.h"
#include "XCpuUsage.h"
#include "XFilesystemUsage.h"
#include "XLoad.h"
#include "XMachineCheckException.h"
#include "XProcessStats.h"
#include "XNicPerformance.h"
#include "XDiskUsage.h"
#include "XIpmi.h"
#include "XLatencyBucketMeasure.h"
#include "XHugePages.h"
#include "XMemoryUsage.h"
#include "XJsonObject.h"

namespace vagt
{
    namespace encode
    {
        enum XEnumMeasurementFieldsMeasurementFieldsVersion
        {
            XEnumMeasurementFieldsMeasurementFieldsVersion4_0,
        };

        class XMeasurementFields : public XExtendEvent
        {
        public:

            virtual std::string toString() = 0;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() = 0;

            virtual void setCodecUsageArray(const XArrayOfXCodecsInUse& codecUsageArray) = 0;
            virtual void setFeatureUsageArray(const XHashMap& featureUsageArray) = 0;
            virtual void setConfiguredEntities(XInteger configuredEntities) = 0;
            virtual void setAdditionalMeasurements(const XArrayOfNamedHashMap& additionalMeasurements) = 0;
            virtual void setCpuUsageArray(const XArrayOfXCpuUsage& cpuUsageArray) = 0;
            virtual void setRequestRate(XNumber requestRate) = 0;
            virtual void setFilesystemUsageArray(const XArrayOfXFilesystemUsage& filesystemUsageArray) = 0;
            virtual void setLoadArray(const XArrayOfXLoad& loadArray) = 0;
            virtual void setMeasurementInterval(XNumber measurementInterval) = 0;
            virtual void setMachineCheckExceptionArray(const XArrayOfXMachineCheckException& machineCheckExceptionArray) = 0;
            virtual void setMeanRequestLatency(XNumber meanRequestLatency) = 0;
            virtual void setConcurrentSessions(XInteger concurrentSessions) = 0;
            virtual void setAdditionalFields(const XHashMap& additionalFields) = 0;
            virtual void setProcessStatsArray(const XArrayOfXProcessStats& processStatsArray) = 0;
            virtual void setNicPerformanceArray(const XArrayOfXNicPerformance& nicPerformanceArray) = 0;
            virtual void setDiskUsageArray(const XArrayOfXDiskUsage& diskUsageArray) = 0;
            virtual void setIpmi(const XIpmi& ipmi) = 0;
            virtual void setLatencyDistribution(const XArrayOfXLatencyBucketMeasure& latencyDistribution) = 0;
            virtual void setHugePagesArray(const XArrayOfXHugePages& hugePagesArray) = 0;
            virtual void setAdditionalObjects(const XArrayOfJsonObject& additionalObjects) = 0;
            virtual void setMemoryUsageArray(const XArrayOfXMemoryUsage& memoryUsageArray) = 0;
            virtual void setNumberOfMediaPortsInUse(XInteger numberOfMediaPortsInUse) = 0;
            virtual void setNfcScalingMetric(XInteger nfcScalingMetric) = 0;

            static std::shared_ptr<XMeasurementFields> create(std::shared_ptr<XCommonEventHeader> header, XNumber measurementInterval);
        };
    }
}
        