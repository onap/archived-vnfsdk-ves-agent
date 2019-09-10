#include "XEndOfCallVqmSummariesImp.h"

const std::string XEnumEndOfCallVqmSummariesEndpointDescriptionMapping[] = {
    "Caller",
    "Callee"
};

XEndOfCallVqmSummariesImp::XEndOfCallVqmSummariesImp(const XString& adjacencyName,
    XEnumEndOfCallVqmSummariesEndpointDescription endpointDescription):
        adjacencyName_(adjacencyName),
        endpointDescription_(endpointDescription)
{

}

void XEndOfCallVqmSummariesImp::setLocalRtpPacketsDiscarded(XNumber localRtpPacketsDiscarded)
{
    comVals_["localRtpPacketsDiscarded"] = localRtpPacketsDiscarded;
}
            
void XEndOfCallVqmSummariesImp::setLocalMaxJitter(XNumber localMaxJitter)
{
    comVals_["localMaxJitter"] = localMaxJitter;
}
            
void XEndOfCallVqmSummariesImp::setRoundTripDelay(XNumber roundTripDelay)
{
    comVals_["roundTripDelay"] = roundTripDelay;
}
            
void XEndOfCallVqmSummariesImp::setLocalRtpOctetsSent(XNumber localRtpOctetsSent)
{
    comVals_["localRtpOctetsSent"] = localRtpOctetsSent;
}
            
void XEndOfCallVqmSummariesImp::setLocalAverageJitterBufferDelay(XNumber localAverageJitterBufferDelay)
{
    comVals_["localAverageJitterBufferDelay"] = localAverageJitterBufferDelay;
}
            
void XEndOfCallVqmSummariesImp::setLocalRtpPacketsLost(XNumber localRtpPacketsLost)
{
    comVals_["localRtpPacketsLost"] = localRtpPacketsLost;
}
            
void XEndOfCallVqmSummariesImp::setEndpointRtpOctetsReceived(XNumber endpointRtpOctetsReceived)
{
    comVals_["endpointRtpOctetsReceived"] = endpointRtpOctetsReceived;
}
            
void XEndOfCallVqmSummariesImp::setRFactor(XNumber rFactor)
{
    comVals_["rFactor"] = rFactor;
}
            
void XEndOfCallVqmSummariesImp::setLocalRtpPacketsReceived(XNumber localRtpPacketsReceived)
{
    comVals_["localRtpPacketsReceived"] = localRtpPacketsReceived;
}
            
void XEndOfCallVqmSummariesImp::setEndpointRtpPacketsLost(XNumber endpointRtpPacketsLost)
{
    comVals_["endpointRtpPacketsLost"] = endpointRtpPacketsLost;
}
            
void XEndOfCallVqmSummariesImp::setLocalAverageJitter(XNumber localAverageJitter)
{
    comVals_["localAverageJitter"] = localAverageJitter;
}
            
void XEndOfCallVqmSummariesImp::setMosCqe(XNumber mosCqe)
{
    comVals_["mosCqe"] = mosCqe;
}
            
void XEndOfCallVqmSummariesImp::setOneWayDelay(XNumber oneWayDelay)
{
    comVals_["oneWayDelay"] = oneWayDelay;
}
            
void XEndOfCallVqmSummariesImp::setEndpointRtpOctetsLost(XNumber endpointRtpOctetsLost)
{
    comVals_["endpointRtpOctetsLost"] = endpointRtpOctetsLost;
}
            
void XEndOfCallVqmSummariesImp::setAdjacencyName(const XString& adjacencyName)
{
    comVals_["adjacencyName"] = adjacencyName;
}
            
void XEndOfCallVqmSummariesImp::setPacketLossPercent(XNumber packetLossPercent)
{
    comVals_["packetLossPercent"] = packetLossPercent;
}
            
void XEndOfCallVqmSummariesImp::setEndpointRtpOctetsDiscarded(XNumber endpointRtpOctetsDiscarded)
{
    comVals_["endpointRtpOctetsDiscarded"] = endpointRtpOctetsDiscarded;
}
            
void XEndOfCallVqmSummariesImp::setLocalRtpPacketsSent(XNumber localRtpPacketsSent)
{
    comVals_["localRtpPacketsSent"] = localRtpPacketsSent;
}
            
void XEndOfCallVqmSummariesImp::setEndpointAverageJitter(XNumber endpointAverageJitter)
{
    comVals_["endpointAverageJitter"] = endpointAverageJitter;
}
            
void XEndOfCallVqmSummariesImp::setEndpointRtpOctetsSent(XNumber endpointRtpOctetsSent)
{
    comVals_["endpointRtpOctetsSent"] = endpointRtpOctetsSent;
}
            
void XEndOfCallVqmSummariesImp::setEndpointMaxJitter(XNumber endpointMaxJitter)
{
    comVals_["endpointMaxJitter"] = endpointMaxJitter;
}
            
void XEndOfCallVqmSummariesImp::setEndpointRtpPacketsReceived(XNumber endpointRtpPacketsReceived)
{
    comVals_["endpointRtpPacketsReceived"] = endpointRtpPacketsReceived;
}
            
void XEndOfCallVqmSummariesImp::setEndpointRtpPacketsSent(XNumber endpointRtpPacketsSent)
{
    comVals_["endpointRtpPacketsSent"] = endpointRtpPacketsSent;
}
            
void XEndOfCallVqmSummariesImp::setLocalMaxJitterBufferDelay(XNumber localMaxJitterBufferDelay)
{
    comVals_["localMaxJitterBufferDelay"] = localMaxJitterBufferDelay;
}
            
void XEndOfCallVqmSummariesImp::setLocalRtpOctetsLost(XNumber localRtpOctetsLost)
{
    comVals_["localRtpOctetsLost"] = localRtpOctetsLost;
}
            
void XEndOfCallVqmSummariesImp::setLocalRtpOctetsReceived(XNumber localRtpOctetsReceived)
{
    comVals_["localRtpOctetsReceived"] = localRtpOctetsReceived;
}
            
void XEndOfCallVqmSummariesImp::setEndpointRtpPacketsDiscarded(XNumber endpointRtpPacketsDiscarded)
{
    comVals_["endpointRtpPacketsDiscarded"] = endpointRtpPacketsDiscarded;
}
            
void XEndOfCallVqmSummariesImp::setEndpointDescription(XEnumEndOfCallVqmSummariesEndpointDescription endpointDescription)
{
    auto val = XEnumEndOfCallVqmSummariesEndpointDescriptionMapping[endpointDescription];
    comVals_["endpointDescription"] = val;
}
            
void XEndOfCallVqmSummariesImp::setLocalRtpOctetsDiscarded(XNumber localRtpOctetsDiscarded)
{
    comVals_["localRtpOctetsDiscarded"] = localRtpOctetsDiscarded;
}

json XEndOfCallVqmSummariesImp::toJson()
{
    try
    {
        if (adjacencyName_.empty())
        {
            return json();
        }

        json field = {
            {"adjacencyName", adjacencyName_},
            {"endpointDescription", XEnumEndOfCallVqmSummariesEndpointDescriptionMapping[endpointDescription_]}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XEndOfCallVqmSummaries to json object:{}.", e.what());
        return json();
    }
}
            