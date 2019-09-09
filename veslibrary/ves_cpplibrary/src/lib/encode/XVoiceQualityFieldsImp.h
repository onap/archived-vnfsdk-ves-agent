#pragma once
        
#include "XVoiceQualityFields.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XVoiceQualityFieldsImp : public XVoiceQualityFields, public XJsonable
        {
        public:
            XVoiceQualityFieldsImp(std::shared_ptr<XCommonEventHeader> header,
                const XString& calleeSideCodec,
                const XString& callerSideCodec,
                const XString& correlator,
                const XString& midCallRtcp,
                const XVendorNfNameFields& vendorNfNameFields);

            virtual std::string toString() override;

            virtual json toJson() override;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() override;

            virtual void setMidCallRtcp(const XString& midCallRtcp) override;
            virtual void setAdditionalInformation(const XHashMap& additionalInformation) override;
            virtual void setEndOfCallVqmSummaries(const XEndOfCallVqmSummaries& endOfCallVqmSummaries) override;
            virtual void setCalleeSideCodec(const XString& calleeSideCodec) override;
            virtual void setPhoneNumber(const XString& phoneNumber) override;
            virtual void setCallerSideCodec(const XString& callerSideCodec) override;
            virtual void setCorrelator(const XString& correlator) override;
            virtual void setVendorNfNameFields(const XVendorNfNameFields& vendorNfNameFields) override;

        private:
            //required
            std::shared_ptr<XCommonEventHeader> header_;
            XString midCallRtcp_;
            XString calleeSideCodec_;
            XString callerSideCodec_;
            XString correlator_;
            XVendorNfNameFields vendorNfNameFields_;
            XEnumVoiceQualityFieldsVoiceQualityFieldsVersion voiceQualityFieldsVersion_;
            //optional
            XHashMap additionalInformation_;
            std::shared_ptr<XEndOfCallVqmSummaries> endOfCallVqmSummaries_;
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        