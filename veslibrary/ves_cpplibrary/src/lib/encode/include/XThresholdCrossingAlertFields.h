#pragma once
        
#include "XCommonEventHeader.h"
#include "XCounter.h"

namespace vagt
{
    namespace encode
    {
        enum XEnumThresholdCrossingAlertFieldsAlertAction
        {
            XEnumThresholdCrossingAlertFieldsAlertActionCLEAR,
            XEnumThresholdCrossingAlertFieldsAlertActionCONT,
            XEnumThresholdCrossingAlertFieldsAlertActionSET,
        };

        enum XEnumThresholdCrossingAlertFieldsAlertType
        {
            XEnumThresholdCrossingAlertFieldsAlertTypeCARD_ANOMALY,
            XEnumThresholdCrossingAlertFieldsAlertTypeELEMENT_ANOMALY,
            XEnumThresholdCrossingAlertFieldsAlertTypeINTERFACE_ANOMALY,
            XEnumThresholdCrossingAlertFieldsAlertTypeSERVICE_ANOMALY,
        };

        enum XEnumThresholdCrossingAlertFieldsEventSeverity
        {
            XEnumThresholdCrossingAlertFieldsEventSeverityCRITICAL,
            XEnumThresholdCrossingAlertFieldsEventSeverityMAJOR,
            XEnumThresholdCrossingAlertFieldsEventSeverityMINOR,
            XEnumThresholdCrossingAlertFieldsEventSeverityWARNING,
            XEnumThresholdCrossingAlertFieldsEventSeverityNORMAL,
        };

        enum XEnumThresholdCrossingAlertFieldsThresholdCrossingFieldsVersion
        {
            XEnumThresholdCrossingAlertFieldsThresholdCrossingFieldsVersion4_0,
        };

        class XThresholdCrossingAlertFields : public XExtendEvent
        {
        public:
            virtual std::string toString() = 0;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() = 0;

            virtual void setAlertDescription(const XString& alertDescription)= 0;
            virtual void setAlertType(XEnumThresholdCrossingAlertFieldsAlertType alertType)= 0;
            virtual void setInterfaceName(const XString& interfaceName)= 0;
            virtual void setCollectionTimestamp(const XString& collectionTimestamp)= 0;
            virtual void setEventSeverity(XEnumThresholdCrossingAlertFieldsEventSeverity eventSeverity)= 0;
            virtual void setPossibleRootCause(const XString& possibleRootCause)= 0;
            virtual void setAssociatedAlertIdList(const XArrayOfString& associatedAlertIdList)= 0;
            virtual void setAlertValue(const XString& alertValue)= 0;
            virtual void setDataCollector(const XString& dataCollector)= 0;
            virtual void setAdditionalParameters(const XArrayOfXCounter& additionalParameters)= 0;
            virtual void setAlertAction(XEnumThresholdCrossingAlertFieldsAlertAction alertAction)= 0;
            virtual void setNetworkService(const XString& networkService)= 0;
            virtual void setElementType(const XString& elementType)= 0;
            virtual void setAdditionalFields(const XHashMap& additionalFields)= 0;
            virtual void setEventStartTimestamp(const XString& eventStartTimestamp)= 0;

            static std::shared_ptr<XThresholdCrossingAlertFields> create(std::shared_ptr<XCommonEventHeader> header,
                XEnumThresholdCrossingAlertFieldsAlertAction alertAction,
                XEnumThresholdCrossingAlertFieldsAlertType alertType,
                XEnumThresholdCrossingAlertFieldsEventSeverity eventSeverity,
                const XString& alertDescription,
                const XString& collectionTimestamp,
                const XString& eventStartTimestamp,
                const XArrayOfXCounter& additionalParameters
                );
        };
    }
}
        