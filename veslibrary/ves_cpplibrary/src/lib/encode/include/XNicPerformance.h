#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        enum XEnumNicPerformanceAdministrativeState
        {
            XEnumNicPerformanceAdministrativeStateInService,
            XEnumNicPerformanceAdministrativeStateOutOfService,
        };

        enum XEnumNicPerformanceOperationalState
        {
            XEnumNicPerformanceOperationalStateInService,
            XEnumNicPerformanceOperationalStateOutOfService,
        };

        enum XEnumNicPerformanceValuesAreSuspect
        {
            XEnumNicPerformanceValuesAreSuspectTrue,
            XEnumNicPerformanceValuesAreSuspectFalse,
        };

        class XNicPerformance 
        {
        public:
            XNicPerformance(const XString& nicIdentifier,
                XEnumNicPerformanceValuesAreSuspect valuesAreSuspect);

            virtual void setTransmittedErrorPacketsDelta(XNumber transmittedErrorPacketsDelta) ;
            virtual void setReceivedErrorPacketsAccumulated(XNumber receivedErrorPacketsAccumulated) ;
            virtual void setTransmittedDiscardedPacketsDelta(XNumber transmittedDiscardedPacketsDelta) ;
            virtual void setReceivedOctetsDelta(XNumber receivedOctetsDelta) ;
            virtual void setReceivedMulticastPacketsDelta(XNumber receivedMulticastPacketsDelta) ;
            virtual void setTransmittedDiscardedPacketsAccumulated(XNumber transmittedDiscardedPacketsAccumulated) ;
            virtual void setTransmittedMulticastPacketsAccumulated(XNumber transmittedMulticastPacketsAccumulated) ;
            virtual void setReceivedDiscardedPacketsDelta(XNumber receivedDiscardedPacketsDelta) ;
            virtual void setReceivedOctetsAccumulated(XNumber receivedOctetsAccumulated) ;
            virtual void setTransmittedTotalPacketsAccumulated(XNumber transmittedTotalPacketsAccumulated) ;
            virtual void setTransmittedOctetsAccumulated(XNumber transmittedOctetsAccumulated) ;
            virtual void setSpeed(XNumber speed) ;
            virtual void setReceivedDiscardedPacketsAccumulated(XNumber receivedDiscardedPacketsAccumulated) ;
            virtual void setReceivedBroadcastPacketsDelta(XNumber receivedBroadcastPacketsDelta) ;
            virtual void setReceivedPercentDiscard(XNumber receivedPercentDiscard) ;
            virtual void setValuesAreSuspect(XEnumNicPerformanceValuesAreSuspect valuesAreSuspect) ;
            virtual void setTransmittedPercentDiscard(XNumber transmittedPercentDiscard) ;
            virtual void setTransmittedErrorPacketsAccumulated(XNumber transmittedErrorPacketsAccumulated) ;
            virtual void setTransmittedBroadcastPacketsAccumulated(XNumber transmittedBroadcastPacketsAccumulated) ;
            virtual void setReceivedTotalPacketsAccumulated(XNumber receivedTotalPacketsAccumulated) ;
            virtual void setReceivedUnicastPacketsAccumulated(XNumber receivedUnicastPacketsAccumulated) ;
            virtual void setTransmittedBroadcastPacketsDelta(XNumber transmittedBroadcastPacketsDelta) ;
            virtual void setTransmittedMulticastPacketsDelta(XNumber transmittedMulticastPacketsDelta) ;
            virtual void setReceivedMulticastPacketsAccumulated(XNumber receivedMulticastPacketsAccumulated) ;
            virtual void setReceivedTotalPacketsDelta(XNumber receivedTotalPacketsDelta) ;
            virtual void setReceivedPercentError(XNumber receivedPercentError) ;
            virtual void setReceivedErrorPacketsDelta(XNumber receivedErrorPacketsDelta) ;
            virtual void setTransmittedOctetsDelta(XNumber transmittedOctetsDelta) ;
            virtual void setNicIdentifier(const XString& nicIdentifier) ;
            virtual void setOperationalState(XEnumNicPerformanceOperationalState operationalState) ;
            virtual void setTransmittedUnicastPacketsAccumulated(XNumber transmittedUnicastPacketsAccumulated) ;
            virtual void setReceivedUnicastPacketsDelta(XNumber receivedUnicastPacketsDelta) ;
            virtual void setTransmittedUtilization(XNumber transmittedUtilization) ;
            virtual void setReceivedBroadcastPacketsAccumulated(XNumber receivedBroadcastPacketsAccumulated) ;
            virtual void setTransmittedUnicastPacketsDelta(XNumber transmittedUnicastPacketsDelta) ;
            virtual void setReceivedUtilization(XNumber receivedUtilization) ;
            virtual void setAdministrativeState(XEnumNicPerformanceAdministrativeState administrativeState) ;
            virtual void setTransmittedPercentError(XNumber transmittedPercentError) ;
            virtual void setTransmittedTotalPacketsDelta(XNumber transmittedTotalPacketsDelta) ;

            std::shared_ptr<XNicPerformance> imp_;

        protected:
            XNicPerformance();
        };

        using XArrayOfXNicPerformance = std::vector<XNicPerformance>;
    }
}
        