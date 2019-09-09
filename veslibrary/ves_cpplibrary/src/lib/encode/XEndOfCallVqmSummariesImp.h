#pragma once
        
#include "XEndOfCallVqmSummaries.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XEndOfCallVqmSummariesImp : public XEndOfCallVqmSummaries, public XJsonable
        {
        public:
            XEndOfCallVqmSummariesImp(const XString& adjacencyName,
                XEnumEndOfCallVqmSummariesEndpointDescription endpointDescription);

            virtual json toJson() override;

            virtual void setLocalRtpPacketsDiscarded(XNumber localRtpPacketsDiscarded) override;
            virtual void setLocalMaxJitter(XNumber localMaxJitter) override;
            virtual void setRoundTripDelay(XNumber roundTripDelay) override;
            virtual void setLocalRtpOctetsSent(XNumber localRtpOctetsSent) override;
            virtual void setLocalAverageJitterBufferDelay(XNumber localAverageJitterBufferDelay) override;
            virtual void setLocalRtpPacketsLost(XNumber localRtpPacketsLost) override;
            virtual void setEndpointRtpOctetsReceived(XNumber endpointRtpOctetsReceived) override;
            virtual void setRFactor(XNumber rFactor) override;
            virtual void setLocalRtpPacketsReceived(XNumber localRtpPacketsReceived) override;
            virtual void setEndpointRtpPacketsLost(XNumber endpointRtpPacketsLost) override;
            virtual void setLocalAverageJitter(XNumber localAverageJitter) override;
            virtual void setMosCqe(XNumber mosCqe) override;
            virtual void setOneWayDelay(XNumber oneWayDelay) override;
            virtual void setEndpointRtpOctetsLost(XNumber endpointRtpOctetsLost) override;
            virtual void setAdjacencyName(const XString& adjacencyName) override;
            virtual void setPacketLossPercent(XNumber packetLossPercent) override;
            virtual void setEndpointRtpOctetsDiscarded(XNumber endpointRtpOctetsDiscarded) override;
            virtual void setLocalRtpPacketsSent(XNumber localRtpPacketsSent) override;
            virtual void setEndpointAverageJitter(XNumber endpointAverageJitter) override;
            virtual void setEndpointRtpOctetsSent(XNumber endpointRtpOctetsSent) override;
            virtual void setEndpointMaxJitter(XNumber endpointMaxJitter) override;
            virtual void setEndpointRtpPacketsReceived(XNumber endpointRtpPacketsReceived) override;
            virtual void setEndpointRtpPacketsSent(XNumber endpointRtpPacketsSent) override;
            virtual void setLocalMaxJitterBufferDelay(XNumber localMaxJitterBufferDelay) override;
            virtual void setLocalRtpOctetsLost(XNumber localRtpOctetsLost) override;
            virtual void setLocalRtpOctetsReceived(XNumber localRtpOctetsReceived) override;
            virtual void setEndpointRtpPacketsDiscarded(XNumber endpointRtpPacketsDiscarded) override;
            virtual void setEndpointDescription(XEnumEndOfCallVqmSummariesEndpointDescription endpointDescription) override;
            virtual void setLocalRtpOctetsDiscarded(XNumber localRtpOctetsDiscarded) override;

        private:
            //required
            XString adjacencyName_;
            XEnumEndOfCallVqmSummariesEndpointDescription endpointDescription_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        