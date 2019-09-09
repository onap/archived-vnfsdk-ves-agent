#include "XVoiceQualityFields.h"
#include "XVoiceQualityFieldsImp.h"

std::shared_ptr<XVoiceQualityFields> vagt::encode::XVoiceQualityFields::create(std::shared_ptr<XCommonEventHeader> header, const XString & calleeSideCodec, const XString & callerSideCodec, const XString & correlator, const XString & midCallRtcp, const XVendorNfNameFields & vendorNfNameFields)
{
    return std::make_shared<XVoiceQualityFieldsImp>(header, 
                calleeSideCodec,
                callerSideCodec,
                correlator,
                midCallRtcp,
                vendorNfNameFields);
}
