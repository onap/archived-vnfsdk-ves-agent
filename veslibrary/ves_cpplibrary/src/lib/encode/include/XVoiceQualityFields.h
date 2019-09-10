#pragma once
        
#include "XCommonEventHeader.h"
#include "XVendorNfNameFields.h"
#include "XEndOfCallVqmSummaries.h"

namespace vagt
{
    namespace encode
    {
        enum XEnumVoiceQualityFieldsVoiceQualityFieldsVersion
        {
            XEnumVoiceQualityFieldsVoiceQualityFieldsVersion4_0,
        };

        class XVoiceQualityFields : public XExtendEvent
        {
        public:
             virtual std::string toString() = 0;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() = 0;

            virtual void setMidCallRtcp(const XString& midCallRtcp) = 0;
            virtual void setAdditionalInformation(const XHashMap& additionalInformation) = 0;
            virtual void setEndOfCallVqmSummaries(const XEndOfCallVqmSummaries& endOfCallVqmSummaries) = 0;
            virtual void setCalleeSideCodec(const XString& calleeSideCodec) = 0;
            virtual void setPhoneNumber(const XString& phoneNumber) = 0;
            virtual void setCallerSideCodec(const XString& callerSideCodec) = 0;
            virtual void setCorrelator(const XString& correlator) = 0;
            virtual void setVendorNfNameFields(const XVendorNfNameFields& vendorNfNameFields) = 0;

            static std::shared_ptr<XVoiceQualityFields> create(std::shared_ptr<XCommonEventHeader> header,
                const XString& calleeSideCodec,
                const XString& callerSideCodec,
                const XString& correlator,
                const XString& midCallRtcp,
                const XVendorNfNameFields& vendorNfNameFields);
        };
    }
}
        