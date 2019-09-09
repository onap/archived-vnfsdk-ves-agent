#include "XGtpPerFlowMetrics.h"
#include "XGtpPerFlowMetricsImp.h"

vagt::encode::XGtpPerFlowMetrics::XGtpPerFlowMetrics()
{
}

vagt::encode::XGtpPerFlowMetrics::XGtpPerFlowMetrics(XNumber avgBitErrorRate, XNumber avgPacketDelayVariation, XNumber avgPacketLatency, XNumber avgReceiveThroughput, XNumber avgTransmitThroughput, XNumber flowActivationEpoch, XNumber flowActivationMicrosec, XNumber flowDeactivationEpoch, XNumber flowDeactivationMicrosec, const XString & flowDeactivationTime, const XString & flowStatus, XNumber maxPacketDelayVariation, XNumber numActivationFailures, XNumber numBitErrors, XNumber numBytesReceived, XNumber numBytesTransmitted, XNumber numDroppedPackets, XNumber numL7BytesReceived, XNumber numL7BytesTransmitted, XNumber numLostPackets, XNumber numOutOfOrderPackets, XNumber numPacketErrors, XNumber numPacketsReceivedExclRetrans, XNumber numPacketsReceivedInclRetrans, XNumber numPacketsTransmittedInclRetrans, XNumber numRetries, XNumber numTimeouts, XNumber numTunneledL7BytesReceived, XNumber roundTripTime, XNumber timeToFirstByte):
    imp_(make_shared<XGtpPerFlowMetricsImp>(avgBitErrorRate,
                avgPacketDelayVariation,
                avgPacketLatency,
                avgReceiveThroughput,
                avgTransmitThroughput,
                flowActivationEpoch,
                flowActivationMicrosec,
                flowDeactivationEpoch,
                flowDeactivationMicrosec,
                flowDeactivationTime,
                flowStatus,
                maxPacketDelayVariation,
                numActivationFailures,
                numBitErrors,
                numBytesReceived,
                numBytesTransmitted,
                numDroppedPackets,
                numL7BytesReceived,
                numL7BytesTransmitted,
                numLostPackets,
                numOutOfOrderPackets,
                numPacketErrors,
                numPacketsReceivedExclRetrans,
                numPacketsReceivedInclRetrans,
                numPacketsTransmittedInclRetrans,
                numRetries,
                numTimeouts,
                numTunneledL7BytesReceived,
                roundTripTime,
                timeToFirstByte
        ))
{
}

void vagt::encode::XGtpPerFlowMetrics::setNumLostPackets(XNumber numLostPackets)
{
    return imp_->setNumLostPackets(numLostPackets);
}

void vagt::encode::XGtpPerFlowMetrics::setNumPacketsReceivedExclRetrans(XNumber numPacketsReceivedExclRetrans)
{
    return imp_->setNumPacketsReceivedExclRetrans(numPacketsReceivedExclRetrans);
}

void vagt::encode::XGtpPerFlowMetrics::setFlowActivationTime(const XString & flowActivationTime)
{
    return imp_->setFlowActivationTime(flowActivationTime);
}

void vagt::encode::XGtpPerFlowMetrics::setFlowDeactivationMicrosec(XNumber flowDeactivationMicrosec)
{
    return imp_->setFlowDeactivationMicrosec(flowDeactivationMicrosec);
}

void vagt::encode::XGtpPerFlowMetrics::setFlowDeactivationTime(const XString & flowDeactivationTime)
{
    return imp_->setFlowDeactivationTime(flowDeactivationTime);
}

void vagt::encode::XGtpPerFlowMetrics::setAvgTransmitThroughput(XNumber avgTransmitThroughput)
{
    return imp_->setAvgTransmitThroughput(avgTransmitThroughput);
}

void vagt::encode::XGtpPerFlowMetrics::setLargePacketRtt(XNumber largePacketRtt)
{
    return imp_->setLargePacketRtt(largePacketRtt);
}

void vagt::encode::XGtpPerFlowMetrics::setNumHttpErrors(XNumber numHttpErrors)
{
    return imp_->setNumHttpErrors(numHttpErrors);
}

void vagt::encode::XGtpPerFlowMetrics::setNumTimeouts(XNumber numTimeouts)
{
    return imp_->setNumTimeouts(numTimeouts);
}

void vagt::encode::XGtpPerFlowMetrics::setFlowActivationEpoch(XNumber flowActivationEpoch)
{
    return imp_->setFlowActivationEpoch(flowActivationEpoch);
}

void vagt::encode::XGtpPerFlowMetrics::setNumPacketErrors(XNumber numPacketErrors)
{
    return imp_->setNumPacketErrors(numPacketErrors);
}

void vagt::encode::XGtpPerFlowMetrics::setAvgPacketDelayVariation(XNumber avgPacketDelayVariation)
{
    return imp_->setAvgPacketDelayVariation(avgPacketDelayVariation);
}

void vagt::encode::XGtpPerFlowMetrics::setAvgBitErrorRate(XNumber avgBitErrorRate)
{
    return imp_->setAvgBitErrorRate(avgBitErrorRate);
}

void vagt::encode::XGtpPerFlowMetrics::setFlowActivationMicrosec(XNumber flowActivationMicrosec)
{
    return imp_->setFlowActivationMicrosec(flowActivationMicrosec);
}

void vagt::encode::XGtpPerFlowMetrics::setAvgPacketLatency(XNumber avgPacketLatency)
{
    return imp_->setAvgPacketLatency(avgPacketLatency);
}

void vagt::encode::XGtpPerFlowMetrics::setNumBytesTransmitted(XNumber numBytesTransmitted)
{
    return imp_->setNumBytesTransmitted(numBytesTransmitted);
}

void vagt::encode::XGtpPerFlowMetrics::setNumBitErrors(XNumber numBitErrors)
{
    return imp_->setNumBitErrors(numBitErrors);
}

void vagt::encode::XGtpPerFlowMetrics::setMaxReceiveBitRate(XNumber maxReceiveBitRate)
{
    return imp_->setMaxReceiveBitRate(maxReceiveBitRate);
}

void vagt::encode::XGtpPerFlowMetrics::setMaxTransmitBitRate(XNumber maxTransmitBitRate)
{
    return imp_->setMaxTransmitBitRate(maxTransmitBitRate);
}

void vagt::encode::XGtpPerFlowMetrics::setAvgReceiveThroughput(XNumber avgReceiveThroughput)
{
    return imp_->setAvgReceiveThroughput(avgReceiveThroughput);
}

void vagt::encode::XGtpPerFlowMetrics::setFlowActivatedBy(const XString & flowActivatedBy)
{
    return imp_->setFlowActivatedBy(flowActivatedBy);
}

void vagt::encode::XGtpPerFlowMetrics::setNumRetries(XNumber numRetries)
{
    return imp_->setNumRetries(numRetries);
}

void vagt::encode::XGtpPerFlowMetrics::setDurConnectionFailedStatus(XNumber durConnectionFailedStatus)
{
    return imp_->setDurConnectionFailedStatus(durConnectionFailedStatus);
}

void vagt::encode::XGtpPerFlowMetrics::setIpTosCountList(const XHashMap & ipTosCountList)
{
    return imp_->setIpTosCountList(ipTosCountList);
}

void vagt::encode::XGtpPerFlowMetrics::setNumL7BytesTransmitted(XNumber numL7BytesTransmitted)
{
    return imp_->setNumL7BytesTransmitted(numL7BytesTransmitted);
}

void vagt::encode::XGtpPerFlowMetrics::setTimeToFirstByte(XNumber timeToFirstByte)
{
    return imp_->setTimeToFirstByte(timeToFirstByte);
}

void vagt::encode::XGtpPerFlowMetrics::setNumBytesReceived(XNumber numBytesReceived)
{
    return imp_->setNumBytesReceived(numBytesReceived);
}

void vagt::encode::XGtpPerFlowMetrics::setFlowDeactivationEpoch(XNumber flowDeactivationEpoch)
{
    return imp_->setFlowDeactivationEpoch(flowDeactivationEpoch);
}

void vagt::encode::XGtpPerFlowMetrics::setNumGtpEchoFailures(XNumber numGtpEchoFailures)
{
    return imp_->setNumGtpEchoFailures(numGtpEchoFailures);
}

void vagt::encode::XGtpPerFlowMetrics::setNumPacketsReceivedInclRetrans(XNumber numPacketsReceivedInclRetrans)
{
    return imp_->setNumPacketsReceivedInclRetrans(numPacketsReceivedInclRetrans);
}

void vagt::encode::XGtpPerFlowMetrics::setMobileQciCosCountList(const XHashMap & mobileQciCosCountList)
{
    return imp_->setMobileQciCosCountList(mobileQciCosCountList);
}

void vagt::encode::XGtpPerFlowMetrics::setNumGtpTunnelErrors(XNumber numGtpTunnelErrors)
{
    return imp_->setNumGtpTunnelErrors(numGtpTunnelErrors);
}

void vagt::encode::XGtpPerFlowMetrics::setRoundTripTime(XNumber roundTripTime)
{
    return imp_->setRoundTripTime(roundTripTime);
}

void vagt::encode::XGtpPerFlowMetrics::setNumActivationFailures(XNumber numActivationFailures)
{
    return imp_->setNumActivationFailures(numActivationFailures);
}

void vagt::encode::XGtpPerFlowMetrics::setMaxPacketDelayVariation(XNumber maxPacketDelayVariation)
{
    return imp_->setMaxPacketDelayVariation(maxPacketDelayVariation);
}

void vagt::encode::XGtpPerFlowMetrics::setNumTunneledL7BytesReceived(XNumber numTunneledL7BytesReceived)
{
    return imp_->setNumTunneledL7BytesReceived(numTunneledL7BytesReceived);
}

void vagt::encode::XGtpPerFlowMetrics::setNumL7BytesReceived(XNumber numL7BytesReceived)
{
    return imp_->setNumL7BytesReceived(numL7BytesReceived);
}

void vagt::encode::XGtpPerFlowMetrics::setIpTosList(const XArrayOfString & ipTosList)
{
    return imp_->setIpTosList(ipTosList);
}

void vagt::encode::XGtpPerFlowMetrics::setMobileQciCosList(const XArrayOfString & mobileQciCosList)
{
    return imp_->setMobileQciCosList(mobileQciCosList);
}

void vagt::encode::XGtpPerFlowMetrics::setGtpConnectionStatus(const XString & gtpConnectionStatus)
{
    return imp_->setGtpConnectionStatus(gtpConnectionStatus);
}

void vagt::encode::XGtpPerFlowMetrics::setTcpFlagList(const XArrayOfString & tcpFlagList)
{
    return imp_->setTcpFlagList(tcpFlagList);
}

void vagt::encode::XGtpPerFlowMetrics::setFlowStatus(const XString & flowStatus)
{
    return imp_->setFlowStatus(flowStatus);
}

void vagt::encode::XGtpPerFlowMetrics::setNumDroppedPackets(XNumber numDroppedPackets)
{
    return imp_->setNumDroppedPackets(numDroppedPackets);
}

void vagt::encode::XGtpPerFlowMetrics::setGtpTunnelStatus(const XString & gtpTunnelStatus)
{
    return imp_->setGtpTunnelStatus(gtpTunnelStatus);
}

void vagt::encode::XGtpPerFlowMetrics::setNumPacketsTransmittedInclRetrans(XNumber numPacketsTransmittedInclRetrans)
{
    return imp_->setNumPacketsTransmittedInclRetrans(numPacketsTransmittedInclRetrans);
}

void vagt::encode::XGtpPerFlowMetrics::setNumOutOfOrderPackets(XNumber numOutOfOrderPackets)
{
    return imp_->setNumOutOfOrderPackets(numOutOfOrderPackets);
}

void vagt::encode::XGtpPerFlowMetrics::setLargePacketThreshold(XNumber largePacketThreshold)
{
    return imp_->setLargePacketThreshold(largePacketThreshold);
}

void vagt::encode::XGtpPerFlowMetrics::setDurTunnelFailedStatus(XNumber durTunnelFailedStatus)
{
    return imp_->setDurTunnelFailedStatus(durTunnelFailedStatus);
}

void vagt::encode::XGtpPerFlowMetrics::setTcpFlagCountList(const XHashMap & tcpFlagCountList)
{
    return imp_->setTcpFlagCountList(tcpFlagCountList);
}

void vagt::encode::XGtpPerFlowMetrics::setFlowDeactivatedBy(const XString & flowDeactivatedBy)
{
    return imp_->setFlowDeactivatedBy(flowDeactivatedBy);
}
