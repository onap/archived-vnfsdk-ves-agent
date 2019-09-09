#include "XNicPerformance.h"
#include "XNicPerformanceImp.h"

vagt::encode::XNicPerformance::XNicPerformance()
{
}

vagt::encode::XNicPerformance::XNicPerformance(const XString & nicIdentifier, XEnumNicPerformanceValuesAreSuspect valuesAreSuspect):
    imp_(make_shared<XNicPerformanceImp>(nicIdentifier, valuesAreSuspect))
{
}

void vagt::encode::XNicPerformance::setTransmittedErrorPacketsDelta(XNumber transmittedErrorPacketsDelta)
{
    return imp_->setTransmittedErrorPacketsDelta(transmittedErrorPacketsDelta);
}

void vagt::encode::XNicPerformance::setReceivedErrorPacketsAccumulated(XNumber receivedErrorPacketsAccumulated)
{
    return imp_->setReceivedErrorPacketsAccumulated(receivedErrorPacketsAccumulated);
}

void vagt::encode::XNicPerformance::setTransmittedDiscardedPacketsDelta(XNumber transmittedDiscardedPacketsDelta)
{
    return imp_->setTransmittedDiscardedPacketsDelta(transmittedDiscardedPacketsDelta);
}

void vagt::encode::XNicPerformance::setReceivedOctetsDelta(XNumber receivedOctetsDelta)
{
    return imp_->setReceivedOctetsDelta(receivedOctetsDelta);
}

void vagt::encode::XNicPerformance::setReceivedMulticastPacketsDelta(XNumber receivedMulticastPacketsDelta)
{
    return imp_->setReceivedMulticastPacketsDelta(receivedMulticastPacketsDelta);
}

void vagt::encode::XNicPerformance::setTransmittedDiscardedPacketsAccumulated(XNumber transmittedDiscardedPacketsAccumulated)
{
    return imp_->setTransmittedDiscardedPacketsAccumulated(transmittedDiscardedPacketsAccumulated);
}

void vagt::encode::XNicPerformance::setTransmittedMulticastPacketsAccumulated(XNumber transmittedMulticastPacketsAccumulated)
{
    return imp_->setTransmittedMulticastPacketsAccumulated(transmittedMulticastPacketsAccumulated);
}

void vagt::encode::XNicPerformance::setReceivedDiscardedPacketsDelta(XNumber receivedDiscardedPacketsDelta)
{
    return imp_->setReceivedDiscardedPacketsDelta(receivedDiscardedPacketsDelta);
}

void vagt::encode::XNicPerformance::setReceivedOctetsAccumulated(XNumber receivedOctetsAccumulated)
{
    return imp_->setReceivedOctetsAccumulated(receivedOctetsAccumulated);
}

void vagt::encode::XNicPerformance::setTransmittedTotalPacketsAccumulated(XNumber transmittedTotalPacketsAccumulated)
{
    return imp_->setTransmittedTotalPacketsAccumulated(transmittedTotalPacketsAccumulated);
}

void vagt::encode::XNicPerformance::setTransmittedOctetsAccumulated(XNumber transmittedOctetsAccumulated)
{
    return imp_->setTransmittedOctetsAccumulated(transmittedOctetsAccumulated);
}

void vagt::encode::XNicPerformance::setSpeed(XNumber speed)
{
    return imp_->setSpeed(speed);
}

void vagt::encode::XNicPerformance::setReceivedDiscardedPacketsAccumulated(XNumber receivedDiscardedPacketsAccumulated)
{
    return imp_->setReceivedDiscardedPacketsAccumulated(receivedDiscardedPacketsAccumulated);
}

void vagt::encode::XNicPerformance::setReceivedBroadcastPacketsDelta(XNumber receivedBroadcastPacketsDelta)
{
    return imp_->setReceivedBroadcastPacketsDelta(receivedBroadcastPacketsDelta);
}

void vagt::encode::XNicPerformance::setReceivedPercentDiscard(XNumber receivedPercentDiscard)
{
    return imp_->setReceivedPercentDiscard(receivedPercentDiscard);
}

void vagt::encode::XNicPerformance::setValuesAreSuspect(XEnumNicPerformanceValuesAreSuspect valuesAreSuspect)
{
    return imp_->setValuesAreSuspect(valuesAreSuspect);
}

void vagt::encode::XNicPerformance::setTransmittedPercentDiscard(XNumber transmittedPercentDiscard)
{
    return imp_->setTransmittedPercentDiscard(transmittedPercentDiscard);
}

void vagt::encode::XNicPerformance::setTransmittedErrorPacketsAccumulated(XNumber transmittedErrorPacketsAccumulated)
{
    return imp_->setTransmittedErrorPacketsAccumulated(transmittedErrorPacketsAccumulated);
}

void vagt::encode::XNicPerformance::setTransmittedBroadcastPacketsAccumulated(XNumber transmittedBroadcastPacketsAccumulated)
{
    return imp_->setTransmittedBroadcastPacketsAccumulated(transmittedBroadcastPacketsAccumulated);
}

void vagt::encode::XNicPerformance::setReceivedTotalPacketsAccumulated(XNumber receivedTotalPacketsAccumulated)
{
    return imp_->setReceivedTotalPacketsAccumulated(receivedTotalPacketsAccumulated);
}

void vagt::encode::XNicPerformance::setReceivedUnicastPacketsAccumulated(XNumber receivedUnicastPacketsAccumulated)
{
    return imp_->setReceivedUnicastPacketsAccumulated(receivedUnicastPacketsAccumulated);
}

void vagt::encode::XNicPerformance::setTransmittedBroadcastPacketsDelta(XNumber transmittedBroadcastPacketsDelta)
{
    return imp_->setTransmittedBroadcastPacketsDelta(transmittedBroadcastPacketsDelta);
}

void vagt::encode::XNicPerformance::setTransmittedMulticastPacketsDelta(XNumber transmittedMulticastPacketsDelta)
{
    return imp_->setTransmittedMulticastPacketsDelta(transmittedMulticastPacketsDelta);
}

void vagt::encode::XNicPerformance::setReceivedMulticastPacketsAccumulated(XNumber receivedMulticastPacketsAccumulated)
{
    return imp_->setReceivedMulticastPacketsAccumulated(receivedMulticastPacketsAccumulated);
}

void vagt::encode::XNicPerformance::setReceivedTotalPacketsDelta(XNumber receivedTotalPacketsDelta)
{
    return imp_->setReceivedTotalPacketsDelta(receivedTotalPacketsDelta);
}

void vagt::encode::XNicPerformance::setReceivedPercentError(XNumber receivedPercentError)
{
    return imp_->setReceivedPercentError(receivedPercentError);
}

void vagt::encode::XNicPerformance::setReceivedErrorPacketsDelta(XNumber receivedErrorPacketsDelta)
{
    return imp_->setReceivedErrorPacketsDelta(receivedErrorPacketsDelta);
}

void vagt::encode::XNicPerformance::setTransmittedOctetsDelta(XNumber transmittedOctetsDelta)
{
    return imp_->setTransmittedOctetsDelta(transmittedOctetsDelta);
}

void vagt::encode::XNicPerformance::setNicIdentifier(const XString & nicIdentifier)
{
    return imp_->setNicIdentifier(nicIdentifier);
}

void vagt::encode::XNicPerformance::setOperationalState(XEnumNicPerformanceOperationalState operationalState)
{
    return imp_->setOperationalState(operationalState);
}

void vagt::encode::XNicPerformance::setTransmittedUnicastPacketsAccumulated(XNumber transmittedUnicastPacketsAccumulated)
{
    return imp_->setTransmittedUnicastPacketsAccumulated(transmittedUnicastPacketsAccumulated);
}

void vagt::encode::XNicPerformance::setReceivedUnicastPacketsDelta(XNumber receivedUnicastPacketsDelta)
{
    return imp_->setReceivedUnicastPacketsDelta(receivedUnicastPacketsDelta);
}

void vagt::encode::XNicPerformance::setTransmittedUtilization(XNumber transmittedUtilization)
{
    return imp_->setTransmittedUtilization(transmittedUtilization);
}

void vagt::encode::XNicPerformance::setReceivedBroadcastPacketsAccumulated(XNumber receivedBroadcastPacketsAccumulated)
{
    return imp_->setReceivedBroadcastPacketsAccumulated(receivedBroadcastPacketsAccumulated);
}

void vagt::encode::XNicPerformance::setTransmittedUnicastPacketsDelta(XNumber transmittedUnicastPacketsDelta)
{
    return imp_->setTransmittedUnicastPacketsDelta(transmittedUnicastPacketsDelta);
}

void vagt::encode::XNicPerformance::setReceivedUtilization(XNumber receivedUtilization)
{
    return imp_->setReceivedUtilization(receivedUtilization);
}

void vagt::encode::XNicPerformance::setAdministrativeState(XEnumNicPerformanceAdministrativeState administrativeState)
{
    return imp_->setAdministrativeState(administrativeState);
}

void vagt::encode::XNicPerformance::setTransmittedPercentError(XNumber transmittedPercentError)
{
    return imp_->setTransmittedPercentError(transmittedPercentError);
}

void vagt::encode::XNicPerformance::setTransmittedTotalPacketsDelta(XNumber transmittedTotalPacketsDelta)
{
    return imp_->setTransmittedTotalPacketsDelta(transmittedTotalPacketsDelta);
}
