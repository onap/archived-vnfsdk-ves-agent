#pragma once
        
#include "XCommonEventHeader.h"

namespace vagt
{
    namespace encode
    {
        enum XEnumPnfRegistrationFieldsPnfRegistrationFieldsVersion
        {
            XEnumPnfRegistrationFieldsPnfRegistrationFieldsVersion2_0,
        };

        class XPnfRegistrationFields : public XExtendEvent
        {
        public:

            virtual std::string toString() = 0;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() = 0;

            virtual void setMacAddress(const XString& macAddress) = 0;
            virtual void setUnitFamily(const XString& unitFamily) = 0;
            virtual void setSerialNumber(const XString& serialNumber) = 0;
            virtual void setUnitType(const XString& unitType) = 0;
            virtual void setManufactureDate(const XString& manufactureDate) = 0;
            virtual void setSoftwareVersion(const XString& softwareVersion) = 0;
            virtual void setModelNumber(const XString& modelNumber) = 0;
            virtual void setLastServiceDate(const XString& lastServiceDate) = 0;
            virtual void setOamV6IpAddress(const XString& oamV6IpAddress) = 0;
            virtual void setAdditionalFields(const XHashMap& additionalFields) = 0;
            virtual void setVendorName(const XString& vendorName) = 0;
            virtual void setOamV4IpAddress(const XString& oamV4IpAddress) = 0;

            static std::shared_ptr<XPnfRegistrationFields> create(std::shared_ptr<XCommonEventHeader> header);
        };
    }
}
        