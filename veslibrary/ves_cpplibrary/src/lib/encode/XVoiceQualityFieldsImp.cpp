#include "XVoiceQualityFieldsImp.h"

const std::string XEnumVoiceQualityFieldsVoiceQualityFieldsVersionMapping[] = {
    "4.0"
};

XVoiceQualityFieldsImp::XVoiceQualityFieldsImp(std::shared_ptr<XCommonEventHeader> header,
                const XString& calleeSideCodec,
                const XString& callerSideCodec,
                const XString& correlator,
                const XString& midCallRtcp,
                const XVendorNfNameFields& vendorNfNameFields):
        header_(header),
        calleeSideCodec_(calleeSideCodec),
        callerSideCodec_(callerSideCodec),
        correlator_(correlator),
        midCallRtcp_(midCallRtcp),
        vendorNfNameFields_(vendorNfNameFields),
        voiceQualityFieldsVersion_(XEnumVoiceQualityFieldsVoiceQualityFieldsVersion4_0)
{

}

std::string XVoiceQualityFieldsImp::toString()
{
    try
    {
        auto js = toJson();
        return js.dump();
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to dump XVoiceQualityFields to json string:{}.", e.what());
        return "";
    }
}

void XVoiceQualityFieldsImp::setMidCallRtcp(const XString& midCallRtcp)
{
    comVals_["midCallRtcp"] = midCallRtcp;
}
            
void XVoiceQualityFieldsImp::setAdditionalInformation(const XHashMap& additionalInformation)
{
    additionalInformation_ = additionalInformation;
}
            
void XVoiceQualityFieldsImp::setEndOfCallVqmSummaries(const XEndOfCallVqmSummaries& endOfCallVqmSummaries)
{
    endOfCallVqmSummaries_ = endOfCallVqmSummaries.imp_;
}
            
void XVoiceQualityFieldsImp::setCalleeSideCodec(const XString& calleeSideCodec)
{
    comVals_["calleeSideCodec"] = calleeSideCodec;
}
            
void XVoiceQualityFieldsImp::setPhoneNumber(const XString& phoneNumber)
{
    comVals_["phoneNumber"] = phoneNumber;
}
            
void XVoiceQualityFieldsImp::setCallerSideCodec(const XString& callerSideCodec)
{
    comVals_["callerSideCodec"] = callerSideCodec;
}
            
void XVoiceQualityFieldsImp::setCorrelator(const XString& correlator)
{
    comVals_["correlator"] = correlator;
}
            
void XVoiceQualityFieldsImp::setVendorNfNameFields(const XVendorNfNameFields& vendorNfNameFields)
{
    vendorNfNameFields_ = vendorNfNameFields;
}

json XVoiceQualityFieldsImp::toJson()
{
    try
    {
        json field = {
            {"midCallRtcp", midCallRtcp_},
            {"calleeSideCodec", calleeSideCodec_},
            {"callerSideCodec", callerSideCodec_},
            {"correlator", correlator_},
            {"vendorNfNameFields", dynamic_pointer_cast<XJsonable>(vendorNfNameFields_.imp_)->toJson()},
            {"voiceQualityFieldsVersion", XEnumVoiceQualityFieldsVoiceQualityFieldsVersionMapping[voiceQualityFieldsVersion_]}
        };

        //optional val
        if (!additionalInformation_.empty())
        {
            field["additionalInformation"] = additionalInformation_;
        }

        if (endOfCallVqmSummaries_)
        {
            auto endOfCallVqmSummaries = dynamic_pointer_cast<XJsonable>(endOfCallVqmSummaries_);
            if (endOfCallVqmSummaries && !endOfCallVqmSummaries->toJson().empty())
            {
                field["endOfCallVqmSummaries"] =  endOfCallVqmSummaries->toJson();
            }
        }

        field = mergeCommonValues(field, comVals_);

        json jsEvent;
        header_->setDomain(XEnumCommonEventHeaderDomainVoiceQuality);
        jsEvent["event"]["commonEventHeader"] = dynamic_pointer_cast<XJsonable>(header_)->toJson();
        jsEvent["event"]["voiceQualityFields"] = field;

        return jsEvent;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XVoiceQualityFields to json object:{}.", e.what());
        return json();
    }
}

std::shared_ptr<XCommonEventHeader> XVoiceQualityFieldsImp::getCommonHeader()
{
    return header_;
}
            