#include "XNicPerformanceImp.h"

const std::string XEnumNicPerformanceValuesAreSuspectMapping[] = {
    "true",
    "false"
};

const std::string XEnumNicPerformanceOperationalStateMapping[] = {
    "inService",
    "outOfService"
};

const std::string XEnumNicPerformanceAdministrativeStateMapping[] = {
    "inService",
    "outOfService"
};

XNicPerformanceImp::XNicPerformanceImp(const XString& nicIdentifier,
    XEnumNicPerformanceValuesAreSuspect valuesAreSuspect):
        nicIdentifier_(nicIdentifier),
        valuesAreSuspect_(valuesAreSuspect)
{

}


void XNicPerformanceImp::setTransmittedErrorPacketsDelta(XNumber transmittedErrorPacketsDelta)
{
    comVals_["transmittedErrorPacketsDelta"] = transmittedErrorPacketsDelta;
}
            
void XNicPerformanceImp::setReceivedErrorPacketsAccumulated(XNumber receivedErrorPacketsAccumulated)
{
    comVals_["receivedErrorPacketsAccumulated"] = receivedErrorPacketsAccumulated;
}
            
void XNicPerformanceImp::setTransmittedDiscardedPacketsDelta(XNumber transmittedDiscardedPacketsDelta)
{
    comVals_["transmittedDiscardedPacketsDelta"] = transmittedDiscardedPacketsDelta;
}
            
void XNicPerformanceImp::setReceivedOctetsDelta(XNumber receivedOctetsDelta)
{
    comVals_["receivedOctetsDelta"] = receivedOctetsDelta;
}
            
void XNicPerformanceImp::setReceivedMulticastPacketsDelta(XNumber receivedMulticastPacketsDelta)
{
    comVals_["receivedMulticastPacketsDelta"] = receivedMulticastPacketsDelta;
}
            
void XNicPerformanceImp::setTransmittedDiscardedPacketsAccumulated(XNumber transmittedDiscardedPacketsAccumulated)
{
    comVals_["transmittedDiscardedPacketsAccumulated"] = transmittedDiscardedPacketsAccumulated;
}
            
void XNicPerformanceImp::setTransmittedMulticastPacketsAccumulated(XNumber transmittedMulticastPacketsAccumulated)
{
    comVals_["transmittedMulticastPacketsAccumulated"] = transmittedMulticastPacketsAccumulated;
}
            
void XNicPerformanceImp::setReceivedDiscardedPacketsDelta(XNumber receivedDiscardedPacketsDelta)
{
    comVals_["receivedDiscardedPacketsDelta"] = receivedDiscardedPacketsDelta;
}
            
void XNicPerformanceImp::setReceivedOctetsAccumulated(XNumber receivedOctetsAccumulated)
{
    comVals_["receivedOctetsAccumulated"] = receivedOctetsAccumulated;
}
            
void XNicPerformanceImp::setTransmittedTotalPacketsAccumulated(XNumber transmittedTotalPacketsAccumulated)
{
    comVals_["transmittedTotalPacketsAccumulated"] = transmittedTotalPacketsAccumulated;
}
            
void XNicPerformanceImp::setTransmittedOctetsAccumulated(XNumber transmittedOctetsAccumulated)
{
    comVals_["transmittedOctetsAccumulated"] = transmittedOctetsAccumulated;
}
            
void XNicPerformanceImp::setSpeed(XNumber speed)
{
    comVals_["speed"] = speed;
}
            
void XNicPerformanceImp::setReceivedDiscardedPacketsAccumulated(XNumber receivedDiscardedPacketsAccumulated)
{
    comVals_["receivedDiscardedPacketsAccumulated"] = receivedDiscardedPacketsAccumulated;
}
            
void XNicPerformanceImp::setReceivedBroadcastPacketsDelta(XNumber receivedBroadcastPacketsDelta)
{
    comVals_["receivedBroadcastPacketsDelta"] = receivedBroadcastPacketsDelta;
}
            
void XNicPerformanceImp::setReceivedPercentDiscard(XNumber receivedPercentDiscard)
{
    comVals_["receivedPercentDiscard"] = receivedPercentDiscard;
}
            
void XNicPerformanceImp::setValuesAreSuspect(XEnumNicPerformanceValuesAreSuspect valuesAreSuspect)
{
    auto val = XEnumNicPerformanceValuesAreSuspectMapping[valuesAreSuspect];
    comVals_["valuesAreSuspect"] = val;
}
            
void XNicPerformanceImp::setTransmittedPercentDiscard(XNumber transmittedPercentDiscard)
{
    comVals_["transmittedPercentDiscard"] = transmittedPercentDiscard;
}
            
void XNicPerformanceImp::setTransmittedErrorPacketsAccumulated(XNumber transmittedErrorPacketsAccumulated)
{
    comVals_["transmittedErrorPacketsAccumulated"] = transmittedErrorPacketsAccumulated;
}
            
void XNicPerformanceImp::setTransmittedBroadcastPacketsAccumulated(XNumber transmittedBroadcastPacketsAccumulated)
{
    comVals_["transmittedBroadcastPacketsAccumulated"] = transmittedBroadcastPacketsAccumulated;
}
            
void XNicPerformanceImp::setReceivedTotalPacketsAccumulated(XNumber receivedTotalPacketsAccumulated)
{
    comVals_["receivedTotalPacketsAccumulated"] = receivedTotalPacketsAccumulated;
}
            
void XNicPerformanceImp::setReceivedUnicastPacketsAccumulated(XNumber receivedUnicastPacketsAccumulated)
{
    comVals_["receivedUnicastPacketsAccumulated"] = receivedUnicastPacketsAccumulated;
}
            
void XNicPerformanceImp::setTransmittedBroadcastPacketsDelta(XNumber transmittedBroadcastPacketsDelta)
{
    comVals_["transmittedBroadcastPacketsDelta"] = transmittedBroadcastPacketsDelta;
}
            
void XNicPerformanceImp::setTransmittedMulticastPacketsDelta(XNumber transmittedMulticastPacketsDelta)
{
    comVals_["transmittedMulticastPacketsDelta"] = transmittedMulticastPacketsDelta;
}
            
void XNicPerformanceImp::setReceivedMulticastPacketsAccumulated(XNumber receivedMulticastPacketsAccumulated)
{
    comVals_["receivedMulticastPacketsAccumulated"] = receivedMulticastPacketsAccumulated;
}
            
void XNicPerformanceImp::setReceivedTotalPacketsDelta(XNumber receivedTotalPacketsDelta)
{
    comVals_["receivedTotalPacketsDelta"] = receivedTotalPacketsDelta;
}
            
void XNicPerformanceImp::setReceivedPercentError(XNumber receivedPercentError)
{
    comVals_["receivedPercentError"] = receivedPercentError;
}
            
void XNicPerformanceImp::setReceivedErrorPacketsDelta(XNumber receivedErrorPacketsDelta)
{
    comVals_["receivedErrorPacketsDelta"] = receivedErrorPacketsDelta;
}
            
void XNicPerformanceImp::setTransmittedOctetsDelta(XNumber transmittedOctetsDelta)
{
    comVals_["transmittedOctetsDelta"] = transmittedOctetsDelta;
}
            
void XNicPerformanceImp::setNicIdentifier(const XString& nicIdentifier)
{
    comVals_["nicIdentifier"] = nicIdentifier;
}
            
void XNicPerformanceImp::setOperationalState(XEnumNicPerformanceOperationalState operationalState)
{
    auto val = XEnumNicPerformanceOperationalStateMapping[operationalState];
    comVals_["operationalState"] = val;
}
            
void XNicPerformanceImp::setTransmittedUnicastPacketsAccumulated(XNumber transmittedUnicastPacketsAccumulated)
{
    comVals_["transmittedUnicastPacketsAccumulated"] = transmittedUnicastPacketsAccumulated;
}
            
void XNicPerformanceImp::setReceivedUnicastPacketsDelta(XNumber receivedUnicastPacketsDelta)
{
    comVals_["receivedUnicastPacketsDelta"] = receivedUnicastPacketsDelta;
}
            
void XNicPerformanceImp::setTransmittedUtilization(XNumber transmittedUtilization)
{
    comVals_["transmittedUtilization"] = transmittedUtilization;
}
            
void XNicPerformanceImp::setReceivedBroadcastPacketsAccumulated(XNumber receivedBroadcastPacketsAccumulated)
{
    comVals_["receivedBroadcastPacketsAccumulated"] = receivedBroadcastPacketsAccumulated;
}
            
void XNicPerformanceImp::setTransmittedUnicastPacketsDelta(XNumber transmittedUnicastPacketsDelta)
{
    comVals_["transmittedUnicastPacketsDelta"] = transmittedUnicastPacketsDelta;
}
            
void XNicPerformanceImp::setReceivedUtilization(XNumber receivedUtilization)
{
    comVals_["receivedUtilization"] = receivedUtilization;
}
            
void XNicPerformanceImp::setAdministrativeState(XEnumNicPerformanceAdministrativeState administrativeState)
{
    auto val = XEnumNicPerformanceAdministrativeStateMapping[administrativeState];
    comVals_["administrativeState"] = val;
}
            
void XNicPerformanceImp::setTransmittedPercentError(XNumber transmittedPercentError)
{
    comVals_["transmittedPercentError"] = transmittedPercentError;
}
            
void XNicPerformanceImp::setTransmittedTotalPacketsDelta(XNumber transmittedTotalPacketsDelta)
{
    comVals_["transmittedTotalPacketsDelta"] = transmittedTotalPacketsDelta;
}

json XNicPerformanceImp::toJson()
{
    try
    {
        json field = {
            {"valuesAreSuspect", XEnumNicPerformanceValuesAreSuspectMapping[valuesAreSuspect_]},
            {"nicIdentifier", nicIdentifier_}
        };

        //optional val

        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XNicPerformance to json object:{}.", e.what());
        return json();
    }
}
            