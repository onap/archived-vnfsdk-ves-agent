#include "XMeasurementFieldsImp.h"

const std::string XEnumMeasurementFieldsMeasurementFieldsVersionMapping[] = {
    "4.0"
};

XMeasurementFieldsImp::XMeasurementFieldsImp(std::shared_ptr<XCommonEventHeader> header, XNumber measurementInterval):
        header_(header),
        measurementInterval_(measurementInterval),
        measurementFieldsVersion_(XEnumMeasurementFieldsMeasurementFieldsVersion4_0)
{

}

std::string XMeasurementFieldsImp::toString()
{
    try
    {
        auto js = toJson();
        return js.dump();
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to dump XMeasurementFields to json string:{}.", e.what());
        return "";
    }
}

void XMeasurementFieldsImp::setCodecUsageArray(const XArrayOfXCodecsInUse& codecUsageArray)
{
    codecUsageArray_ = codecUsageArray;
}
            
void XMeasurementFieldsImp::setFeatureUsageArray(const XHashMap& featureUsageArray)
{
    featureUsageArray_ = featureUsageArray;
}
            
void XMeasurementFieldsImp::setConfiguredEntities(XInteger configuredEntities)
{
    comVals_["configuredEntities"] = configuredEntities;
}
            
void XMeasurementFieldsImp::setAdditionalMeasurements(const XArrayOfNamedHashMap& additionalMeasurements)
{
    additionalMeasurements_ = additionalMeasurements;
}
            
void XMeasurementFieldsImp::setCpuUsageArray(const XArrayOfXCpuUsage& cpuUsageArray)
{
    cpuUsageArray_ = cpuUsageArray;
}
            
void XMeasurementFieldsImp::setRequestRate(XNumber requestRate)
{
    comVals_["requestRate"] = requestRate;
}
            
void XMeasurementFieldsImp::setFilesystemUsageArray(const XArrayOfXFilesystemUsage& filesystemUsageArray)
{
    filesystemUsageArray_ = filesystemUsageArray;
}
            
void XMeasurementFieldsImp::setLoadArray(const XArrayOfXLoad& loadArray)
{
    loadArray_ = loadArray;
}
            
void XMeasurementFieldsImp::setMeasurementInterval(XNumber measurementInterval)
{
    comVals_["measurementInterval"] = measurementInterval;
}
            
void XMeasurementFieldsImp::setMachineCheckExceptionArray(const XArrayOfXMachineCheckException& machineCheckExceptionArray)
{
    machineCheckExceptionArray_ = machineCheckExceptionArray;
}
            
void XMeasurementFieldsImp::setMeanRequestLatency(XNumber meanRequestLatency)
{
    comVals_["meanRequestLatency"] = meanRequestLatency;
}
            
void XMeasurementFieldsImp::setConcurrentSessions(XInteger concurrentSessions)
{
    comVals_["concurrentSessions"] = concurrentSessions;
}
            
void XMeasurementFieldsImp::setAdditionalFields(const XHashMap& additionalFields)
{
    additionalFields_ = additionalFields;
}
            
void XMeasurementFieldsImp::setProcessStatsArray(const XArrayOfXProcessStats& processStatsArray)
{
    processStatsArray_ = processStatsArray;
}
            
void XMeasurementFieldsImp::setNicPerformanceArray(const XArrayOfXNicPerformance& nicPerformanceArray)
{
    nicPerformanceArray_ = nicPerformanceArray;
}
            
void XMeasurementFieldsImp::setDiskUsageArray(const XArrayOfXDiskUsage& diskUsageArray)
{
    diskUsageArray_ = diskUsageArray;
}
            
void XMeasurementFieldsImp::setIpmi(const XIpmi& ipmi)
{
    ipmi_ = ipmi;
}
            
void XMeasurementFieldsImp::setLatencyDistribution(const XArrayOfXLatencyBucketMeasure& latencyDistribution)
{
    latencyDistribution_ = latencyDistribution;
}
            
void XMeasurementFieldsImp::setHugePagesArray(const XArrayOfXHugePages& hugePagesArray)
{
    hugePagesArray_ = hugePagesArray;
}
            
void XMeasurementFieldsImp::setAdditionalObjects(const XArrayOfJsonObject& additionalObjects)
{
    additionalObjects_ = additionalObjects;
}
            
void XMeasurementFieldsImp::setMemoryUsageArray(const XArrayOfXMemoryUsage& memoryUsageArray)
{
    memoryUsageArray_ = memoryUsageArray;
}
            
void XMeasurementFieldsImp::setNumberOfMediaPortsInUse(XInteger numberOfMediaPortsInUse)
{
    comVals_["numberOfMediaPortsInUse"] = numberOfMediaPortsInUse;
}
            
void XMeasurementFieldsImp::setNfcScalingMetric(XInteger nfcScalingMetric)
{
    comVals_["nfcScalingMetric"] = nfcScalingMetric;
}

std::shared_ptr<XCommonEventHeader> XMeasurementFieldsImp::getCommonHeader()
{
    return header_;
}

json XMeasurementFieldsImp::toJson()
{
    try
    {
        json field = {
            {"measurementFieldsVersion", XEnumMeasurementFieldsMeasurementFieldsVersionMapping[measurementFieldsVersion_]},
            {"measurementInterval", measurementInterval_}
        };

        //optional val
        if (!codecUsageArray_.empty())
        {
            field["codecUsageArray"] = fromArray(codecUsageArray_);
        }

        if (!featureUsageArray_.empty())
        {
            field["featureUsageArray"] = featureUsageArray_;
        }

        if (!additionalMeasurements_.empty())
        {
            field["additionalMeasurements"] = fromArray(additionalMeasurements_);
        }

        if (!cpuUsageArray_.empty())
        {
            field["cpuUsageArray"] = fromArray(cpuUsageArray_);
        }

        if (!filesystemUsageArray_.empty())
        {
            field["filesystemUsageArray"] = fromArray(filesystemUsageArray_);
        }
        
        if (!loadArray_.empty())
        {
            field["loadArray"] = fromArray(loadArray_);
        }

        if (!machineCheckExceptionArray_.empty())
        {
            field["machineCheckExceptionArray"] = fromArray(machineCheckExceptionArray_);
        }

        if (!additionalFields_.empty())
        {
            field["additionalFields"] = additionalFields_;
        }

        if (!processStatsArray_.empty())
        {
            field["processStatsArray"] = fromArray(processStatsArray_);
        }

        if (!nicPerformanceArray_.empty())
        {
            field["nicPerformanceArray"] = fromArray(nicPerformanceArray_);
        }

        if (!diskUsageArray_.empty())
        {
            field["diskUsageArray"] = fromArray(diskUsageArray_);
        }

        auto ipmi = dynamic_pointer_cast<XJsonable>(ipmi_.imp_);
        if (ipmi && !ipmi->toJson().empty())
        {
            field["ipmi"] = ipmi->toJson();
        }

        if (!latencyDistribution_.empty())
        {
            field["latencyDistribution"] = fromArray(latencyDistribution_);
        }

        if (!hugePagesArray_.empty())
        {
            field["hugePagesArray"] = fromArray(hugePagesArray_);
        }

        if (!additionalObjects_.empty())
        {
            field["additionalObjects"] = fromArray(additionalObjects_);
        }

        if (!memoryUsageArray_.empty())
        {
            field["memoryUsageArray"] = fromArray(memoryUsageArray_);
        }

        field = mergeCommonValues(field, comVals_);

        json jsEvent;
        header_->setDomain(XEnumCommonEventHeaderDomainMeasurement);
        jsEvent["event"]["commonEventHeader"] = dynamic_pointer_cast<XJsonable>(header_)->toJson();
        jsEvent["event"]["measurementFields"] = field;

        return jsEvent;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XMeasurementFields to json object:{}.", e.what());
        return json();
    }
}
            