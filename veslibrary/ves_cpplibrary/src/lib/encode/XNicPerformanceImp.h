#pragma once
        
#include "XNicPerformance.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XNicPerformanceImp : public XNicPerformance, public XJsonable
        {
        public:
            XNicPerformanceImp(const XString& nicIdentifier,
                XEnumNicPerformanceValuesAreSuspect valuesAreSuspect);

            virtual json toJson() override;

            virtual void setTransmittedErrorPacketsDelta(XNumber transmittedErrorPacketsDelta) override;
            virtual void setReceivedErrorPacketsAccumulated(XNumber receivedErrorPacketsAccumulated) override;
            virtual void setTransmittedDiscardedPacketsDelta(XNumber transmittedDiscardedPacketsDelta) override;
            virtual void setReceivedOctetsDelta(XNumber receivedOctetsDelta) override;
            virtual void setReceivedMulticastPacketsDelta(XNumber receivedMulticastPacketsDelta) override;
            virtual void setTransmittedDiscardedPacketsAccumulated(XNumber transmittedDiscardedPacketsAccumulated) override;
            virtual void setTransmittedMulticastPacketsAccumulated(XNumber transmittedMulticastPacketsAccumulated) override;
            virtual void setReceivedDiscardedPacketsDelta(XNumber receivedDiscardedPacketsDelta) override;
            virtual void setReceivedOctetsAccumulated(XNumber receivedOctetsAccumulated) override;
            virtual void setTransmittedTotalPacketsAccumulated(XNumber transmittedTotalPacketsAccumulated) override;
            virtual void setTransmittedOctetsAccumulated(XNumber transmittedOctetsAccumulated) override;
            virtual void setSpeed(XNumber speed) override;
            virtual void setReceivedDiscardedPacketsAccumulated(XNumber receivedDiscardedPacketsAccumulated) override;
            virtual void setReceivedBroadcastPacketsDelta(XNumber receivedBroadcastPacketsDelta) override;
            virtual void setReceivedPercentDiscard(XNumber receivedPercentDiscard) override;
            virtual void setValuesAreSuspect(XEnumNicPerformanceValuesAreSuspect valuesAreSuspect) override;
            virtual void setTransmittedPercentDiscard(XNumber transmittedPercentDiscard) override;
            virtual void setTransmittedErrorPacketsAccumulated(XNumber transmittedErrorPacketsAccumulated) override;
            virtual void setTransmittedBroadcastPacketsAccumulated(XNumber transmittedBroadcastPacketsAccumulated) override;
            virtual void setReceivedTotalPacketsAccumulated(XNumber receivedTotalPacketsAccumulated) override;
            virtual void setReceivedUnicastPacketsAccumulated(XNumber receivedUnicastPacketsAccumulated) override;
            virtual void setTransmittedBroadcastPacketsDelta(XNumber transmittedBroadcastPacketsDelta) override;
            virtual void setTransmittedMulticastPacketsDelta(XNumber transmittedMulticastPacketsDelta) override;
            virtual void setReceivedMulticastPacketsAccumulated(XNumber receivedMulticastPacketsAccumulated) override;
            virtual void setReceivedTotalPacketsDelta(XNumber receivedTotalPacketsDelta) override;
            virtual void setReceivedPercentError(XNumber receivedPercentError) override;
            virtual void setReceivedErrorPacketsDelta(XNumber receivedErrorPacketsDelta) override;
            virtual void setTransmittedOctetsDelta(XNumber transmittedOctetsDelta) override;
            virtual void setNicIdentifier(const XString& nicIdentifier) override;
            virtual void setOperationalState(XEnumNicPerformanceOperationalState operationalState) override;
            virtual void setTransmittedUnicastPacketsAccumulated(XNumber transmittedUnicastPacketsAccumulated) override;
            virtual void setReceivedUnicastPacketsDelta(XNumber receivedUnicastPacketsDelta) override;
            virtual void setTransmittedUtilization(XNumber transmittedUtilization) override;
            virtual void setReceivedBroadcastPacketsAccumulated(XNumber receivedBroadcastPacketsAccumulated) override;
            virtual void setTransmittedUnicastPacketsDelta(XNumber transmittedUnicastPacketsDelta) override;
            virtual void setReceivedUtilization(XNumber receivedUtilization) override;
            virtual void setAdministrativeState(XEnumNicPerformanceAdministrativeState administrativeState) override;
            virtual void setTransmittedPercentError(XNumber transmittedPercentError) override;
            virtual void setTransmittedTotalPacketsDelta(XNumber transmittedTotalPacketsDelta) override;

        private:
            //required
            XEnumNicPerformanceValuesAreSuspect valuesAreSuspect_;
            XString nicIdentifier_;
            //optional
            XEnumNicPerformanceOperationalState operationalState_;
            XEnumNicPerformanceAdministrativeState administrativeState_;
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        