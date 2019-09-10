#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XGtpPerFlowMetrics 
        {
        public:
            XGtpPerFlowMetrics(XNumber avgBitErrorRate,
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
                XNumber timeToFirstByte);

            virtual void setNumLostPackets(XNumber numLostPackets);
            virtual void setNumPacketsReceivedExclRetrans(XNumber numPacketsReceivedExclRetrans);
            virtual void setFlowActivationTime(const XString& flowActivationTime);
            virtual void setFlowDeactivationMicrosec(XNumber flowDeactivationMicrosec);
            virtual void setFlowDeactivationTime(const XString& flowDeactivationTime);
            virtual void setAvgTransmitThroughput(XNumber avgTransmitThroughput);
            virtual void setLargePacketRtt(XNumber largePacketRtt);
            virtual void setNumHttpErrors(XNumber numHttpErrors);
            virtual void setNumTimeouts(XNumber numTimeouts);
            virtual void setFlowActivationEpoch(XNumber flowActivationEpoch);
            virtual void setNumPacketErrors(XNumber numPacketErrors);
            virtual void setAvgPacketDelayVariation(XNumber avgPacketDelayVariation);
            virtual void setAvgBitErrorRate(XNumber avgBitErrorRate);
            virtual void setFlowActivationMicrosec(XNumber flowActivationMicrosec);
            virtual void setAvgPacketLatency(XNumber avgPacketLatency);
            virtual void setNumBytesTransmitted(XNumber numBytesTransmitted);
            virtual void setNumBitErrors(XNumber numBitErrors);
            virtual void setMaxReceiveBitRate(XNumber maxReceiveBitRate);
            virtual void setMaxTransmitBitRate(XNumber maxTransmitBitRate);
            virtual void setAvgReceiveThroughput(XNumber avgReceiveThroughput);
            virtual void setFlowActivatedBy(const XString& flowActivatedBy);
            virtual void setNumRetries(XNumber numRetries);
            virtual void setDurConnectionFailedStatus(XNumber durConnectionFailedStatus);
            virtual void setIpTosCountList(const XHashMap& ipTosCountList);
            virtual void setNumL7BytesTransmitted(XNumber numL7BytesTransmitted);
            virtual void setTimeToFirstByte(XNumber timeToFirstByte);
            virtual void setNumBytesReceived(XNumber numBytesReceived);
            virtual void setFlowDeactivationEpoch(XNumber flowDeactivationEpoch);
            virtual void setNumGtpEchoFailures(XNumber numGtpEchoFailures);
            virtual void setNumPacketsReceivedInclRetrans(XNumber numPacketsReceivedInclRetrans);
            virtual void setMobileQciCosCountList(const XHashMap& mobileQciCosCountList);
            virtual void setNumGtpTunnelErrors(XNumber numGtpTunnelErrors);
            virtual void setRoundTripTime(XNumber roundTripTime);
            virtual void setNumActivationFailures(XNumber numActivationFailures);
            virtual void setMaxPacketDelayVariation(XNumber maxPacketDelayVariation);
            virtual void setNumTunneledL7BytesReceived(XNumber numTunneledL7BytesReceived);
            virtual void setNumL7BytesReceived(XNumber numL7BytesReceived);
            virtual void setIpTosList(const XArrayOfString& ipTosList);
            virtual void setMobileQciCosList(const XArrayOfString& mobileQciCosList);
            virtual void setGtpConnectionStatus(const XString& gtpConnectionStatus);
            virtual void setTcpFlagList(const XArrayOfString& tcpFlagList);
            virtual void setFlowStatus(const XString& flowStatus);
            virtual void setNumDroppedPackets(XNumber numDroppedPackets);
            virtual void setGtpTunnelStatus(const XString& gtpTunnelStatus);
            virtual void setNumPacketsTransmittedInclRetrans(XNumber numPacketsTransmittedInclRetrans);
            virtual void setNumOutOfOrderPackets(XNumber numOutOfOrderPackets);
            virtual void setLargePacketThreshold(XNumber largePacketThreshold);
            virtual void setDurTunnelFailedStatus(XNumber durTunnelFailedStatus);
            virtual void setTcpFlagCountList(const XHashMap& tcpFlagCountList);
            virtual void setFlowDeactivatedBy(const XString& flowDeactivatedBy);

            std::shared_ptr<XGtpPerFlowMetrics> imp_;

        protected:
            XGtpPerFlowMetrics();
        };
    }
}
        