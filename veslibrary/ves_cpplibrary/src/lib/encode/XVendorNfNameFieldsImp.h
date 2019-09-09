#pragma once
        
#include "XVendorNfNameFields.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XVendorNfNameFieldsImp : public XVendorNfNameFields, public XJsonable
        {
        public:
            XVendorNfNameFieldsImp(const XString& vendorName);

            virtual json toJson() override;

            virtual void setNfModuleName(const XString& nfModuleName) override;
            virtual void setNfName(const XString& nfName) override;
            virtual void setVendorName(const XString& vendorName) override;

        private:
            //required
            XString vendorName_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        