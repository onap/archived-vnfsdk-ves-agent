#pragma once
        
#include "XCommonEventHeader.h"
#include "XVendorNfNameFields.h"

namespace vagt
{
    namespace encode
    {
        enum XEnumSipSignalingFieldsSipSignalingFieldsVersion
        {
            XEnumSipSignalingFieldsSipSignalingFieldsVersion3_0,
        };

        class XSipSignalingFields : public XExtendEvent
        {
        public:
            virtual std::string toString() = 0;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() = 0;

            virtual void setRemotePort(const XString& remotePort) = 0;
            virtual void setSummarySip(const XString& summarySip) = 0;
            virtual void setLocalPort(const XString& localPort) = 0;
            virtual void setAdditionalInformation(const XHashMap& additionalInformation) = 0;
            virtual void setLocalIpAddress(const XString& localIpAddress) = 0;
            virtual void setCompressedSip(const XString& compressedSip) = 0;
            virtual void setCorrelator(const XString& correlator) = 0;
            virtual void setRemoteIpAddress(const XString& remoteIpAddress) = 0;
            virtual void setVendorNfNameFields(const XVendorNfNameFields& vendorNfNameFields) = 0;

            static std::shared_ptr<XSipSignalingFields> create(std::shared_ptr<XCommonEventHeader> header,
                const XString& correlator,
                const XString& localIpAddress,
                const XString& localPort,
                const XString& remoteIpAddress,
                const XString& remotePort,
                const XVendorNfNameFields& vendorNfNameFields);
        };
    }
}
        