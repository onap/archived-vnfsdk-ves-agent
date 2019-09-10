#include "XGtpPerFlowMetricsImp.h"

XGtpPerFlowMetricsImp::XGtpPerFlowMetricsImp(XNumber avgBitErrorRate,
    XNumber avgPacketDelayVariation,
    XNumber avgPacketLatency,
    XNumber avgReceiveThroughput,
    XNumber avgTransmitThroughput,
    XNumber flowActivationEpoch,
    XNumber flowActivationMicrosec,
    XNumber flowDeactivationEpoch,
    XNumber flowDeactivationMicrosec,
    const XString& flowDeactivationTime,
    const XString& flowStatus,
    XNumber maxPacketDelayVariation,
    XNumber numActivationFailures,
    XNumber numBitErrors,
    XNumber numBytesReceived,
    XNumber numBytesTransmitted,
    XNumber numDroppedPackets,
    XNumber numL7BytesReceived,
    XNumber numL7BytesTransmitted,
    XNumber numLostPackets,
    XNumber numOutOfOrderPackets,
    XNumber numPacketErrors,
    XNumber numPacketsReceivedExclRetrans,
    XNumber numPacketsReceivedInclRetrans,
    XNumber numPacketsTransmittedInclRetrans,
    XNumber numRetries,
    XNumber numTimeouts,
    XNumber numTunneledL7BytesReceived,
    XNumber roundTripTime,
    XNumber timeToFirstByte):
        avgBitErrorRate_(avgBitErrorRate),
        avgPacketDelayVariation_(avgPacketDelayVariation),
        avgPacketLatency_(avgPacketLatency),
        avgReceiveThroughput_(avgReceiveThroughput),
        avgTransmitThroughput_(avgTransmitThroughput),
        flowActivationEpoch_(flowActivationEpoch),
        flowActivationMicrosec_(flowActivationMicrosec),
        flowDeactivationEpoch_(flowDeactivationEpoch),
        flowDeactivationMicrosec_(flowDeactivationMicrosec),
        flowDeactivationTime_(flowDeactivationTime),
        flowStatus_(flowStatus),
        maxPacketDelayVariation_(maxPacketDelayVariation),
        numActivationFailures_(numActivationFailures),
        numBitErrors_(numBitErrors),
        numBytesReceived_(numBytesReceived),
        numBytesTransmitted_(numBytesTransmitted),
        numDroppedPackets_(numDroppedPackets),
        numL7BytesReceived_(numL7BytesReceived),
        numL7BytesTransmitted_(numL7BytesTransmitted),
        numLostPackets_(numLostPackets),
        numOutOfOrderPackets_(numOutOfOrderPackets),
        numPacketErrors_(numPacketErrors),
        numPacketsReceivedExclRetrans_(numPacketsReceivedExclRetrans),
        numPacketsReceivedInclRetrans_(numPacketsReceivedInclRetrans),
        numPacketsTransmittedInclRetrans_(numPacketsTransmittedInclRetrans),
        numRetries_(numRetries),
        numTimeouts_(numTimeouts),
        numTunneledL7BytesReceived_(numTunneledL7BytesReceived),
        roundTripTime_(roundTripTime),
        timeToFirstByte_(timeToFirstByte)
{

}

void XGtpPerFlowMetricsImp::setNumLostPackets(XNumber numLostPackets)
{
    comVals_["numLostPackets"] = numLostPackets;
}
            
void XGtpPerFlowMetricsImp::setNumPacketsReceivedExclRetrans(XNumber numPacketsReceivedExclRetrans)
{
    comVals_["numPacketsReceivedExclRetrans"] = numPacketsReceivedExclRetrans;
}
            
void XGtpPerFlowMetricsImp::setFlowActivationTime(const XString& flowActivationTime)
{
    comVals_["flowActivationTime"] = flowActivationTime;
}
            
void XGtpPerFlowMetricsImp::setFlowDeactivationMicrosec(XNumber flowDeactivationMicrosec)
{
    comVals_["flowDeactivationMicrosec"] = flowDeactivationMicrosec;
}
            
void XGtpPerFlowMetricsImp::setFlowDeactivationTime(const XString& flowDeactivationTime)
{
    comVals_["flowDeactivationTime"] = flowDeactivationTime;
}
            
void XGtpPerFlowMetricsImp::setAvgTransmitThroughput(XNumber avgTransmitThroughput)
{
    comVals_["avgTransmitThroughput"] = avgTransmitThroughput;
}
            
void XGtpPerFlowMetricsImp::setLargePacketRtt(XNumber largePacketRtt)
{
    comVals_["largePacketRtt"] = largePacketRtt;
}
            
void XGtpPerFlowMetricsImp::setNumHttpErrors(XNumber numHttpErrors)
{
    comVals_["numHttpErrors"] = numHttpErrors;
}
            
void XGtpPerFlowMetricsImp::setNumTimeouts(XNumber numTimeouts)
{
    comVals_["numTimeouts"] = numTimeouts;
}
            
void XGtpPerFlowMetricsImp::setFlowActivationEpoch(XNumber flowActivationEpoch)
{
    comVals_["flowActivationEpoch"] = flowActivationEpoch;
}
            
void XGtpPerFlowMetricsImp::setNumPacketErrors(XNumber numPacketErrors)
{
    comVals_["numPacketErrors"] = numPacketErrors;
}
            
void XGtpPerFlowMetricsImp::setAvgPacketDelayVariation(XNumber avgPacketDelayVariation)
{
    comVals_["avgPacketDelayVariation"] = avgPacketDelayVariation;
}
            
void XGtpPerFlowMetricsImp::setAvgBitErrorRate(XNumber avgBitErrorRate)
{
    comVals_["avgBitErrorRate"] = avgBitErrorRate;
}
            
void XGtpPerFlowMetricsImp::setFlowActivationMicrosec(XNumber flowActivationMicrosec)
{
    comVals_["flowActivationMicrosec"] = flowActivationMicrosec;
}
            
void XGtpPerFlowMetricsImp::setAvgPacketLatency(XNumber avgPacketLatency)
{
    comVals_["avgPacketLatency"] = avgPacketLatency;
}
            
void XGtpPerFlowMetricsImp::setNumBytesTransmitted(XNumber numBytesTransmitted)
{
    comVals_["numBytesTransmitted"] = numBytesTransmitted;
}
            
void XGtpPerFlowMetricsImp::setNumBitErrors(XNumber numBitErrors)
{
    comVals_["numBitErrors"] = numBitErrors;
}
            
void XGtpPerFlowMetricsImp::setMaxReceiveBitRate(XNumber maxReceiveBitRate)
{
    comVals_["maxReceiveBitRate"] = maxReceiveBitRate;
}
            
void XGtpPerFlowMetricsImp::setMaxTransmitBitRate(XNumber maxTransmitBitRate)
{
    comVals_["maxTransmitBitRate"] = maxTransmitBitRate;
}
            
void XGtpPerFlowMetricsImp::setAvgReceiveThroughput(XNumber avgReceiveThroughput)
{
    comVals_["avgReceiveThroughput"] = avgReceiveThroughput;
}
            
void XGtpPerFlowMetricsImp::setFlowActivatedBy(const XString& flowActivatedBy)
{
    comVals_["flowActivatedBy"] = flowActivatedBy;
}
            
void XGtpPerFlowMetricsImp::setNumRetries(XNumber numRetries)
{
    comVals_["numRetries"] = numRetries;
}
            
void XGtpPerFlowMetricsImp::setDurConnectionFailedStatus(XNumber durConnectionFailedStatus)
{
    comVals_["durConnectionFailedStatus"] = durConnectionFailedStatus;
}
            
void XGtpPerFlowMetricsImp::setIpTosCountList(const XHashMap& ipTosCountList)
{
    ipTosCountList_ = ipTosCountList;
}
            
void XGtpPerFlowMetricsImp::setNumL7BytesTransmitted(XNumber numL7BytesTransmitted)
{
    comVals_["numL7BytesTransmitted"] = numL7BytesTransmitted;
}
            
void XGtpPerFlowMetricsImp::setTimeToFirstByte(XNumber timeToFirstByte)
{
    comVals_["timeToFirstByte"] = timeToFirstByte;
}
            
void XGtpPerFlowMetricsImp::setNumBytesReceived(XNumber numBytesReceived)
{
    comVals_["numBytesReceived"] = numBytesReceived;
}
            
void XGtpPerFlowMetricsImp::setFlowDeactivationEpoch(XNumber flowDeactivationEpoch)
{
    comVals_["flowDeactivationEpoch"] = flowDeactivationEpoch;
}
            
void XGtpPerFlowMetricsImp::setNumGtpEchoFailures(XNumber numGtpEchoFailures)
{
    comVals_["numGtpEchoFailures"] = numGtpEchoFailures;
}
            
void XGtpPerFlowMetricsImp::setNumPacketsReceivedInclRetrans(XNumber numPacketsReceivedInclRetrans)
{
    comVals_["numPacketsReceivedInclRetrans"] = numPacketsReceivedInclRetrans;
}
            
void XGtpPerFlowMetricsImp::setMobileQciCosCountList(const XHashMap& mobileQciCosCountList)
{
    mobileQciCosCountList_ = mobileQciCosCountList;
}
            
void XGtpPerFlowMetricsImp::setNumGtpTunnelErrors(XNumber numGtpTunnelErrors)
{
    comVals_["numGtpTunnelErrors"] = numGtpTunnelErrors;
}
            
void XGtpPerFlowMetricsImp::setRoundTripTime(XNumber roundTripTime)
{
    comVals_["roundTripTime"] = roundTripTime;
}
            
void XGtpPerFlowMetricsImp::setNumActivationFailures(XNumber numActivationFailures)
{
    comVals_["numActivationFailures"] = numActivationFailures;
}
            
void XGtpPerFlowMetricsImp::setMaxPacketDelayVariation(XNumber maxPacketDelayVariation)
{
    comVals_["maxPacketDelayVariation"] = maxPacketDelayVariation;
}
            
void XGtpPerFlowMetricsImp::setNumTunneledL7BytesReceived(XNumber numTunneledL7BytesReceived)
{
    comVals_["numTunneledL7BytesReceived"] = numTunneledL7BytesReceived;
}
            
void XGtpPerFlowMetricsImp::setNumL7BytesReceived(XNumber numL7BytesReceived)
{
    comVals_["numL7BytesReceived"] = numL7BytesReceived;
}
            
void XGtpPerFlowMetricsImp::setIpTosList(const XArrayOfString& ipTosList)
{
    ipTosList_ = ipTosList;
}
            
void XGtpPerFlowMetricsImp::setMobileQciCosList(const XArrayOfString& mobileQciCosList)
{
    mobileQciCosList_ = mobileQciCosList;
}
            
void XGtpPerFlowMetricsImp::setGtpConnectionStatus(const XString& gtpConnectionStatus)
{
    comVals_["gtpConnectionStatus"] = gtpConnectionStatus;
}
            
void XGtpPerFlowMetricsImp::setTcpFlagList(const XArrayOfString& tcpFlagList)
{
    tcpFlagList_ = tcpFlagList;
}
            
void XGtpPerFlowMetricsImp::setFlowStatus(const XString& flowStatus)
{
    comVals_["flowStatus"] = flowStatus;
}
            
void XGtpPerFlowMetricsImp::setNumDroppedPackets(XNumber numDroppedPackets)
{
    comVals_["numDroppedPackets"] = numDroppedPackets;
}
            
void XGtpPerFlowMetricsImp::setGtpTunnelStatus(const XString& gtpTunnelStatus)
{
    comVals_["gtpTunnelStatus"] = gtpTunnelStatus;
}
            
void XGtpPerFlowMetricsImp::setNumPacketsTransmittedInclRetrans(XNumber numPacketsTransmittedInclRetrans)
{
    comVals_["numPacketsTransmittedInclRetrans"] = numPacketsTransmittedInclRetrans;
}
            
void XGtpPerFlowMetricsImp::setNumOutOfOrderPackets(XNumber numOutOfOrderPackets)
{
    comVals_["numOutOfOrderPackets"] = numOutOfOrderPackets;
}
            
void XGtpPerFlowMetricsImp::setLargePacketThreshold(XNumber largePacketThreshold)
{
    comVals_["largePacketThreshold"] = largePacketThreshold;
}
            
void XGtpPerFlowMetricsImp::setDurTunnelFailedStatus(XNumber durTunnelFailedStatus)
{
    comVals_["durTunnelFailedStatus"] = durTunnelFailedStatus;
}
            
void XGtpPerFlowMetricsImp::setTcpFlagCountList(const XHashMap& tcpFlagCountList)
{
    tcpFlagCountList_ = tcpFlagCountList;
}
            
void XGtpPerFlowMetricsImp::setFlowDeactivatedBy(const XString& flowDeactivatedBy)
{
    comVals_["flowDeactivatedBy"] = flowDeactivatedBy;
}

json XGtpPerFlowMetricsImp::toJson()
{
    try
    {
        json field = {
            {"numLostPackets", numLostPackets_},
            {"numPacketsReceivedExclRetrans", numPacketsReceivedExclRetrans_},
            {"flowDeactivationMicrosec", flowDeactivationMicrosec_},
            {"flowDeactivationTime", flowDeactivationTime_},
            {"avgTransmitThroughput", avgTransmitThroughput_},
            {"numTimeouts", numTimeouts_},
            {"flowActivationEpoch", flowActivationEpoch_},
            {"numPacketErrors", numPacketErrors_},
            {"avgPacketDelayVariation", avgPacketDelayVariation_},
            {"avgBitErrorRate", avgBitErrorRate_},
            {"flowActivationMicrosec", flowActivationMicrosec_},
            {"avgPacketLatency", avgPacketLatency_},
            {"numBytesTransmitted", numBytesTransmitted_},
            {"numBitErrors", numBitErrors_},
            {"avgReceiveThroughput", avgReceiveThroughput_},
            {"numRetries", numRetries_},
            {"numL7BytesTransmitted", numL7BytesTransmitted_},
            {"timeToFirstByte", timeToFirstByte_},
            {"numBytesReceived", numBytesReceived_},
            {"flowDeactivationEpoch", flowDeactivationEpoch_},
            {"numPacketsReceivedInclRetrans", numPacketsReceivedInclRetrans_},
            {"roundTripTime", roundTripTime_},
            {"numActivationFailures", numActivationFailures_},
            {"maxPacketDelayVariation", maxPacketDelayVariation_},
            {"numTunneledL7BytesReceived", numTunneledL7BytesReceived_},
            {"numL7BytesReceived", numL7BytesReceived_},
            {"flowStatus", flowStatus_},
            {"numDroppedPackets", numDroppedPackets_},
            {"numPacketsTransmittedInclRetrans", numPacketsTransmittedInclRetrans_},
            {"numOutOfOrderPackets", numOutOfOrderPackets_}
        };

        //optional val
        if (!ipTosCountList_.empty())
        {
            field["ipTosCountList"] = ipTosCountList_;
        }

        if (!mobileQciCosCountList_.empty())
        {
            field["mobileQciCosCountList"] = mobileQciCosCountList_;
        }

        if (!ipTosList_.empty())
        {
            field["ipTosList"] = ipTosList_;
        }

        if (!mobileQciCosList_.empty())
        {
            field["mobileQciCosList"] = mobileQciCosList_;
        }

        if (!tcpFlagList_.empty())
        {
            field["tcpFlagList"] = tcpFlagList_;
        }

        if (!tcpFlagCountList_.empty())
        {
            field["tcpFlagCountList"] = tcpFlagCountList_;
        }

        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XGtpPerFlowMetrics to json object:{}.", e.what());
        return json();
    }
}
            