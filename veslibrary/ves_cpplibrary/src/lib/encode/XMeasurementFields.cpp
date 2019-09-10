#include "XMeasurementFields.h"
#include "XMeasurementFieldsImp.h"

std::shared_ptr<XMeasurementFields> vagt::encode::XMeasurementFields::create(std::shared_ptr<XCommonEventHeader> header, XNumber measurementInterval)
{
    return std::make_shared<XMeasurementFieldsImp>(header, measurementInterval);
}
