#include "XPnfRegistrationFieldsImp.h"

const std::string XEnumPnfRegistrationFieldsPnfRegistrationFieldsVersionMapping[] = {
    "2.0"
};

XPnfRegistrationFieldsImp::XPnfRegistrationFieldsImp(std::shared_ptr<XCommonEventHeader> header):
        header_(header),
        pnfRegistrationFieldsVersion_(XEnumPnfRegistrationFieldsPnfRegistrationFieldsVersion2_0)
{

}

std::string XPnfRegistrationFieldsImp::toString()
{
    try
    {
        auto js = toJson();
        return js.dump();
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to dump XPnfRegistrationFields to json string:{}.", e.what());
        return "";
    }
}

void XPnfRegistrationFieldsImp::setMacAddress(const XString& macAddress)
{
    comVals_["macAddress"] = macAddress;
}
            
void XPnfRegistrationFieldsImp::setUnitFamily(const XString& unitFamily)
{
    comVals_["unitFamily"] = unitFamily;
}
            
void XPnfRegistrationFieldsImp::setSerialNumber(const XString& serialNumber)
{
    comVals_["serialNumber"] = serialNumber;
}
            
void XPnfRegistrationFieldsImp::setUnitType(const XString& unitType)
{
    comVals_["unitType"] = unitType;
}
            
void XPnfRegistrationFieldsImp::setManufactureDate(const XString& manufactureDate)
{
    comVals_["manufactureDate"] = manufactureDate;
}
            
void XPnfRegistrationFieldsImp::setSoftwareVersion(const XString& softwareVersion)
{
    comVals_["softwareVersion"] = softwareVersion;
}
            
void XPnfRegistrationFieldsImp::setModelNumber(const XString& modelNumber)
{
    comVals_["modelNumber"] = modelNumber;
}
            
void XPnfRegistrationFieldsImp::setLastServiceDate(const XString& lastServiceDate)
{
    comVals_["lastServiceDate"] = lastServiceDate;
}
            
void XPnfRegistrationFieldsImp::setOamV6IpAddress(const XString& oamV6IpAddress)
{
    comVals_["oamV6IpAddress"] = oamV6IpAddress;
}
            
void XPnfRegistrationFieldsImp::setAdditionalFields(const XHashMap& additionalFields)
{
    additionalFields_ = additionalFields;
}
            
void XPnfRegistrationFieldsImp::setVendorName(const XString& vendorName)
{
    comVals_["vendorName"] = vendorName;
}
            
void XPnfRegistrationFieldsImp::setOamV4IpAddress(const XString& oamV4IpAddress)
{
    comVals_["oamV4IpAddress"] = oamV4IpAddress;
}

std::shared_ptr<XCommonEventHeader> XPnfRegistrationFieldsImp::getCommonHeader()
{
    return header_;
}

json XPnfRegistrationFieldsImp::toJson()
{
    try
    {
        json field = {
            {"pnfRegistrationFieldsVersion", XEnumPnfRegistrationFieldsPnfRegistrationFieldsVersionMapping[pnfRegistrationFieldsVersion_]}
        };

        //optional val

        if (!additionalFields_.empty())
        {
            field["additionalFields"] = additionalFields_;
        }

        field = mergeCommonValues(field, comVals_);

        json jsEvent;
        header_->setDomain(XEnumCommonEventHeaderDomainPnfRegistration);
        jsEvent["event"]["commonEventHeader"] = dynamic_pointer_cast<XJsonable>(header_)->toJson();
        jsEvent["event"]["pnfRegistrationFields"] = field;

        return jsEvent;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XPnfRegistrationFields to json object:{}.", e.what());
        return json();
    }
}
            