#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XVendorNfNameFields 
        {
        public:
            XVendorNfNameFields(const XString& vendorName);

            virtual void setNfModuleName(const XString& nfModuleName);
            virtual void setNfName(const XString& nfName);
            virtual void setVendorName(const XString& vendorName);

            std::shared_ptr<XVendorNfNameFields> imp_;

        protected:
            XVendorNfNameFields();
        };
    }
}
        