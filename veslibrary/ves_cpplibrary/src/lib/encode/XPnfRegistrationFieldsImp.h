#pragma once
        
#include "XPnfRegistrationFields.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XPnfRegistrationFieldsImp : public XPnfRegistrationFields, public XJsonable
        {
        public:
            XPnfRegistrationFieldsImp(std::shared_ptr<XCommonEventHeader> header);

            virtual std::string toString() override;

            virtual json toJson() override;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() override;

            virtual void setMacAddress(const XString& macAddress) override;
            virtual void setUnitFamily(const XString& unitFamily) override;
            virtual void setSerialNumber(const XString& serialNumber) override;
            virtual void setUnitType(const XString& unitType) override;
            virtual void setManufactureDate(const XString& manufactureDate) override;
            virtual void setSoftwareVersion(const XString& softwareVersion) override;
            virtual void setModelNumber(const XString& modelNumber) override;
            virtual void setLastServiceDate(const XString& lastServiceDate) override;
            virtual void setOamV6IpAddress(const XString& oamV6IpAddress) override;
            virtual void setAdditionalFields(const XHashMap& additionalFields) override;
            virtual void setVendorName(const XString& vendorName) override;
            virtual void setOamV4IpAddress(const XString& oamV4IpAddress) override;

        private:
            //required
            std::shared_ptr<XCommonEventHeader> header_;
            XEnumPnfRegistrationFieldsPnfRegistrationFieldsVersion pnfRegistrationFieldsVersion_;
            //optional
            XHashMap additionalFields_;
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        