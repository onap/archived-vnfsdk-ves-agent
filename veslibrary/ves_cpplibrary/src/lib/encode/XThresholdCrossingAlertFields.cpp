#include "XThresholdCrossingAlertFields.h"
#include "XThresholdCrossingAlertFieldsImp.h"

std::shared_ptr<XThresholdCrossingAlertFields> vagt::encode::XThresholdCrossingAlertFields::create(std::shared_ptr<XCommonEventHeader> header, XEnumThresholdCrossingAlertFieldsAlertAction alertAction, XEnumThresholdCrossingAlertFieldsAlertType alertType, XEnumThresholdCrossingAlertFieldsEventSeverity eventSeverity, const XString & alertDescription, const XString & collectionTimestamp, const XString & eventStartTimestamp, const XArrayOfXCounter & additionalParameters)
{
    return std::make_shared<XThresholdCrossingAlertFieldsImp>(header,
        alertAction,
        alertType,
        eventSeverity,
        alertDescription,
        collectionTimestamp,
        eventStartTimestamp,
        additionalParameters);
 }
