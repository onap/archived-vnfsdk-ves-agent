#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        enum XEnumEndOfCallVqmSummariesEndpointDescription
        {
            XEnumEndOfCallVqmSummariesEndpointDescriptionCaller,
            XEnumEndOfCallVqmSummariesEndpointDescriptionCallee,
        };

        class XEndOfCallVqmSummaries  
        {
        public:
            XEndOfCallVqmSummaries(const XString& adjacencyName,
                XEnumEndOfCallVqmSummariesEndpointDescription endpointDescription);

            virtual void setLocalRtpPacketsDiscarded(XNumber localRtpPacketsDiscarded);
            virtual void setLocalMaxJitter(XNumber localMaxJitter);
            virtual void setRoundTripDelay(XNumber roundTripDelay);
            virtual void setLocalRtpOctetsSent(XNumber localRtpOctetsSent);
            virtual void setLocalAverageJitterBufferDelay(XNumber localAverageJitterBufferDelay);
            virtual void setLocalRtpPacketsLost(XNumber localRtpPacketsLost);
            virtual void setEndpointRtpOctetsReceived(XNumber endpointRtpOctetsReceived);
            virtual void setRFactor(XNumber rFactor);
            virtual void setLocalRtpPacketsReceived(XNumber localRtpPacketsReceived);
            virtual void setEndpointRtpPacketsLost(XNumber endpointRtpPacketsLost);
            virtual void setLocalAverageJitter(XNumber localAverageJitter);
            virtual void setMosCqe(XNumber mosCqe);
            virtual void setOneWayDelay(XNumber oneWayDelay);
            virtual void setEndpointRtpOctetsLost(XNumber endpointRtpOctetsLost);
            virtual void setAdjacencyName(const XString& adjacencyName);
            virtual void setPacketLossPercent(XNumber packetLossPercent);
            virtual void setEndpointRtpOctetsDiscarded(XNumber endpointRtpOctetsDiscarded);
            virtual void setLocalRtpPacketsSent(XNumber localRtpPacketsSent);
            virtual void setEndpointAverageJitter(XNumber endpointAverageJitter);
            virtual void setEndpointRtpOctetsSent(XNumber endpointRtpOctetsSent);
            virtual void setEndpointMaxJitter(XNumber endpointMaxJitter);
            virtual void setEndpointRtpPacketsReceived(XNumber endpointRtpPacketsReceived);
            virtual void setEndpointRtpPacketsSent(XNumber endpointRtpPacketsSent);
            virtual void setLocalMaxJitterBufferDelay(XNumber localMaxJitterBufferDelay);
            virtual void setLocalRtpOctetsLost(XNumber localRtpOctetsLost);
            virtual void setLocalRtpOctetsReceived(XNumber localRtpOctetsReceived);
            virtual void setEndpointRtpPacketsDiscarded(XNumber endpointRtpPacketsDiscarded);
            virtual void setEndpointDescription(XEnumEndOfCallVqmSummariesEndpointDescription endpointDescription);
            virtual void setLocalRtpOctetsDiscarded(XNumber localRtpOctetsDiscarded);

            std::shared_ptr<XEndOfCallVqmSummaries> imp_;

        protected:
            XEndOfCallVqmSummaries();
        };
    }
}
        