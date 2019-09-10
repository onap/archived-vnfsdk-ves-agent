#include "XEndOfCallVqmSummaries.h"
#include "XEndOfCallVqmSummariesImp.h"

vagt::encode::XEndOfCallVqmSummaries::XEndOfCallVqmSummaries()
{
}

vagt::encode::XEndOfCallVqmSummaries::XEndOfCallVqmSummaries(const XString & adjacencyName, XEnumEndOfCallVqmSummariesEndpointDescription endpointDescription):
    imp_(make_shared<XEndOfCallVqmSummariesImp>(adjacencyName, endpointDescription))
{
}

void vagt::encode::XEndOfCallVqmSummaries::setLocalRtpPacketsDiscarded(XNumber localRtpPacketsDiscarded)
{
    return imp_->setLocalRtpPacketsDiscarded(localRtpPacketsDiscarded);
}

void vagt::encode::XEndOfCallVqmSummaries::setLocalMaxJitter(XNumber localMaxJitter)
{
    return imp_->setLocalMaxJitter(localMaxJitter);
}

void vagt::encode::XEndOfCallVqmSummaries::setRoundTripDelay(XNumber roundTripDelay)
{
    return imp_->setRoundTripDelay(roundTripDelay);
}

void vagt::encode::XEndOfCallVqmSummaries::setLocalRtpOctetsSent(XNumber localRtpOctetsSent)
{
    return imp_->setLocalRtpOctetsSent(localRtpOctetsSent);
}

void vagt::encode::XEndOfCallVqmSummaries::setLocalAverageJitterBufferDelay(XNumber localAverageJitterBufferDelay)
{
    return imp_->setLocalAverageJitterBufferDelay(localAverageJitterBufferDelay);
}

void vagt::encode::XEndOfCallVqmSummaries::setLocalRtpPacketsLost(XNumber localRtpPacketsLost)
{
    return imp_->setLocalRtpPacketsLost(localRtpPacketsLost);
}

void vagt::encode::XEndOfCallVqmSummaries::setEndpointRtpOctetsReceived(XNumber endpointRtpOctetsReceived)
{
    return imp_->setEndpointRtpOctetsReceived(endpointRtpOctetsReceived);
}

void vagt::encode::XEndOfCallVqmSummaries::setRFactor(XNumber rFactor)
{
    return imp_->setRFactor(rFactor);
}

void vagt::encode::XEndOfCallVqmSummaries::setLocalRtpPacketsReceived(XNumber localRtpPacketsReceived)
{
    return imp_->setLocalRtpPacketsReceived(localRtpPacketsReceived);
}

void vagt::encode::XEndOfCallVqmSummaries::setEndpointRtpPacketsLost(XNumber endpointRtpPacketsLost)
{
    return imp_->setEndpointRtpPacketsLost(endpointRtpPacketsLost);
}

void vagt::encode::XEndOfCallVqmSummaries::setLocalAverageJitter(XNumber localAverageJitter)
{
    return imp_->setLocalAverageJitter(localAverageJitter);
}

void vagt::encode::XEndOfCallVqmSummaries::setMosCqe(XNumber mosCqe)
{
    return imp_->setMosCqe(mosCqe);
}

void vagt::encode::XEndOfCallVqmSummaries::setOneWayDelay(XNumber oneWayDelay)
{
    return imp_->setOneWayDelay(oneWayDelay);
}

void vagt::encode::XEndOfCallVqmSummaries::setEndpointRtpOctetsLost(XNumber endpointRtpOctetsLost)
{
    return imp_->setEndpointRtpOctetsLost(endpointRtpOctetsLost);
}

void vagt::encode::XEndOfCallVqmSummaries::setAdjacencyName(const XString & adjacencyName)
{
    return imp_->setAdjacencyName(adjacencyName);
}

void vagt::encode::XEndOfCallVqmSummaries::setPacketLossPercent(XNumber packetLossPercent)
{
    return imp_->setPacketLossPercent(packetLossPercent);
}

void vagt::encode::XEndOfCallVqmSummaries::setEndpointRtpOctetsDiscarded(XNumber endpointRtpOctetsDiscarded)
{
    return imp_->setEndpointRtpOctetsDiscarded(endpointRtpOctetsDiscarded);
}

void vagt::encode::XEndOfCallVqmSummaries::setLocalRtpPacketsSent(XNumber localRtpPacketsSent)
{
    return imp_->setLocalRtpPacketsSent(localRtpPacketsSent);
}

void vagt::encode::XEndOfCallVqmSummaries::setEndpointAverageJitter(XNumber endpointAverageJitter)
{
    return imp_->setEndpointAverageJitter(endpointAverageJitter);
}

void vagt::encode::XEndOfCallVqmSummaries::setEndpointRtpOctetsSent(XNumber endpointRtpOctetsSent)
{
    return imp_->setEndpointRtpOctetsSent(endpointRtpOctetsSent);
}

void vagt::encode::XEndOfCallVqmSummaries::setEndpointMaxJitter(XNumber endpointMaxJitter)
{
    return imp_->setEndpointMaxJitter(endpointMaxJitter);
}

void vagt::encode::XEndOfCallVqmSummaries::setEndpointRtpPacketsReceived(XNumber endpointRtpPacketsReceived)
{
    return imp_->setEndpointRtpPacketsReceived(endpointRtpPacketsReceived);
}

void vagt::encode::XEndOfCallVqmSummaries::setEndpointRtpPacketsSent(XNumber endpointRtpPacketsSent)
{
    return imp_->setEndpointRtpPacketsSent(endpointRtpPacketsSent);
}

void vagt::encode::XEndOfCallVqmSummaries::setLocalMaxJitterBufferDelay(XNumber localMaxJitterBufferDelay)
{
    return imp_->setLocalMaxJitterBufferDelay(localMaxJitterBufferDelay);
}

void vagt::encode::XEndOfCallVqmSummaries::setLocalRtpOctetsLost(XNumber localRtpOctetsLost)
{
    return imp_->setLocalRtpOctetsLost(localRtpOctetsLost);
}

void vagt::encode::XEndOfCallVqmSummaries::setLocalRtpOctetsReceived(XNumber localRtpOctetsReceived)
{
    return imp_->setLocalRtpOctetsReceived(localRtpOctetsReceived);
}

void vagt::encode::XEndOfCallVqmSummaries::setEndpointRtpPacketsDiscarded(XNumber endpointRtpPacketsDiscarded)
{
    return imp_->setEndpointRtpPacketsDiscarded(endpointRtpPacketsDiscarded);
}

void vagt::encode::XEndOfCallVqmSummaries::setEndpointDescription(XEnumEndOfCallVqmSummariesEndpointDescription endpointDescription)
{
    return imp_->setEndpointDescription(endpointDescription);
}

void vagt::encode::XEndOfCallVqmSummaries::setLocalRtpOctetsDiscarded(XNumber localRtpOctetsDiscarded)
{
    return imp_->setLocalRtpOctetsDiscarded(localRtpOctetsDiscarded);
}
