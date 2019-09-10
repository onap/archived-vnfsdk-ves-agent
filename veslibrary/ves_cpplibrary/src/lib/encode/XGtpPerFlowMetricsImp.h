#pragma once
        
#include "XGtpPerFlowMetrics.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XGtpPerFlowMetricsImp : public XGtpPerFlowMetrics, public XJsonable
        {
        public:
            XGtpPerFlowMetricsImp(XNumber avgBitErrorRate,
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

            virtual json toJson() override;

            virtual void setNumLostPackets(XNumber numLostPackets) override;
            virtual void setNumPacketsReceivedExclRetrans(XNumber numPacketsReceivedExclRetrans) override;
            virtual void setFlowActivationTime(const XString& flowActivationTime) override;
            virtual void setFlowDeactivationMicrosec(XNumber flowDeactivationMicrosec) override;
            virtual void setFlowDeactivationTime(const XString& flowDeactivationTime) override;
            virtual void setAvgTransmitThroughput(XNumber avgTransmitThroughput) override;
            virtual void setLargePacketRtt(XNumber largePacketRtt) override;
            virtual void setNumHttpErrors(XNumber numHttpErrors) override;
            virtual void setNumTimeouts(XNumber numTimeouts) override;
            virtual void setFlowActivationEpoch(XNumber flowActivationEpoch) override;
            virtual void setNumPacketErrors(XNumber numPacketErrors) override;
            virtual void setAvgPacketDelayVariation(XNumber avgPacketDelayVariation) override;
            virtual void setAvgBitErrorRate(XNumber avgBitErrorRate) override;
            virtual void setFlowActivationMicrosec(XNumber flowActivationMicrosec) override;
            virtual void setAvgPacketLatency(XNumber avgPacketLatency) override;
            virtual void setNumBytesTransmitted(XNumber numBytesTransmitted) override;
            virtual void setNumBitErrors(XNumber numBitErrors) override;
            virtual void setMaxReceiveBitRate(XNumber maxReceiveBitRate) override;
            virtual void setMaxTransmitBitRate(XNumber maxTransmitBitRate) override;
            virtual void setAvgReceiveThroughput(XNumber avgReceiveThroughput) override;
            virtual void setFlowActivatedBy(const XString& flowActivatedBy) override;
            virtual void setNumRetries(XNumber numRetries) override;
            virtual void setDurConnectionFailedStatus(XNumber durConnectionFailedStatus) override;
            virtual void setIpTosCountList(const XHashMap& ipTosCountList) override;
            virtual void setNumL7BytesTransmitted(XNumber numL7BytesTransmitted) override;
            virtual void setTimeToFirstByte(XNumber timeToFirstByte) override;
            virtual void setNumBytesReceived(XNumber numBytesReceived) override;
            virtual void setFlowDeactivationEpoch(XNumber flowDeactivationEpoch) override;
            virtual void setNumGtpEchoFailures(XNumber numGtpEchoFailures) override;
            virtual void setNumPacketsReceivedInclRetrans(XNumber numPacketsReceivedInclRetrans) override;
            virtual void setMobileQciCosCountList(const XHashMap& mobileQciCosCountList) override;
            virtual void setNumGtpTunnelErrors(XNumber numGtpTunnelErrors) override;
            virtual void setRoundTripTime(XNumber roundTripTime) override;
            virtual void setNumActivationFailures(XNumber numActivationFailures) override;
            virtual void setMaxPacketDelayVariation(XNumber maxPacketDelayVariation) override;
            virtual void setNumTunneledL7BytesReceived(XNumber numTunneledL7BytesReceived) override;
            virtual void setNumL7BytesReceived(XNumber numL7BytesReceived) override;
            virtual void setIpTosList(const XArrayOfString& ipTosList) override;
            virtual void setMobileQciCosList(const XArrayOfString& mobileQciCosList) override;
            virtual void setGtpConnectionStatus(const XString& gtpConnectionStatus) override;
            virtual void setTcpFlagList(const XArrayOfString& tcpFlagList) override;
            virtual void setFlowStatus(const XString& flowStatus) override;
            virtual void setNumDroppedPackets(XNumber numDroppedPackets) override;
            virtual void setGtpTunnelStatus(const XString& gtpTunnelStatus) override;
            virtual void setNumPacketsTransmittedInclRetrans(XNumber numPacketsTransmittedInclRetrans) override;
            virtual void setNumOutOfOrderPackets(XNumber numOutOfOrderPackets) override;
            virtual void setLargePacketThreshold(XNumber largePacketThreshold) override;
            virtual void setDurTunnelFailedStatus(XNumber durTunnelFailedStatus) override;
            virtual void setTcpFlagCountList(const XHashMap& tcpFlagCountList) override;
            virtual void setFlowDeactivatedBy(const XString& flowDeactivatedBy) override;

        private:
            //required
            XNumber numLostPackets_;
            XNumber numPacketsReceivedExclRetrans_;
            XNumber flowDeactivationMicrosec_;
            XString flowDeactivationTime_;
            XNumber avgTransmitThroughput_;
            XNumber numTimeouts_;
            XNumber flowActivationEpoch_;
            XNumber numPacketErrors_;
            XNumber avgPacketDelayVariation_;
            XNumber avgBitErrorRate_;
            XNumber flowActivationMicrosec_;
            XNumber avgPacketLatency_;
            XNumber numBytesTransmitted_;
            XNumber numBitErrors_;
            XNumber avgReceiveThroughput_;
            XNumber numRetries_;
            XNumber numL7BytesTransmitted_;
            XNumber timeToFirstByte_;
            XNumber numBytesReceived_;
            XNumber flowDeactivationEpoch_;
            XNumber numPacketsReceivedInclRetrans_;
            XNumber roundTripTime_;
            XNumber numActivationFailures_;
            XNumber maxPacketDelayVariation_;
            XNumber numTunneledL7BytesReceived_;
            XNumber numL7BytesReceived_;
            XString flowStatus_;
            XNumber numDroppedPackets_;
            XNumber numPacketsTransmittedInclRetrans_;
            XNumber numOutOfOrderPackets_;
            //optional
            XHashMap ipTosCountList_;
            XHashMap mobileQciCosCountList_;
            XArrayOfString ipTosList_;
            XArrayOfString mobileQciCosList_;
            XArrayOfString tcpFlagList_;
            XHashMap tcpFlagCountList_;
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        