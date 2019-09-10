#pragma once
        
#include "XSipSignalingFields.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XSipSignalingFieldsImp : public XSipSignalingFields, public XJsonable
        {
        public:
            XSipSignalingFieldsImp(std::shared_ptr<XCommonEventHeader> header,
                const XString& correlator,
                const XString& localIpAddress,
                const XString& localPort,
                const XString& remoteIpAddress,
                const XString& remotePort,
                const XVendorNfNameFields& vendorNfNameFields);

            virtual std::string toString() override;

            virtual json toJson() override;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() override;

            virtual void setRemotePort(const XString& remotePort) override;
            virtual void setSummarySip(const XString& summarySip) override;
            virtual void setLocalPort(const XString& localPort) override;
            virtual void setAdditionalInformation(const XHashMap& additionalInformation) override;
            virtual void setLocalIpAddress(const XString& localIpAddress) override;
            virtual void setCompressedSip(const XString& compressedSip) override;
            virtual void setCorrelator(const XString& correlator) override;
            virtual void setRemoteIpAddress(const XString& remoteIpAddress) override;
            virtual void setVendorNfNameFields(const XVendorNfNameFields& vendorNfNameFields) override;

        private:
            //required
            std::shared_ptr<XCommonEventHeader> header_;
            XEnumSipSignalingFieldsSipSignalingFieldsVersion sipSignalingFieldsVersion_;
            XString remotePort_;
            XString localPort_;
            XString localIpAddress_;
            XString correlator_;
            XString remoteIpAddress_;
            XVendorNfNameFields vendorNfNameFields_;
            //optional
            XHashMap additionalInformation_;
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        