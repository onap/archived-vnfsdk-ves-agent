#include "XSipSignalingFieldsImp.h"

const std::string XEnumSipSignalingFieldsSipSignalingFieldsVersionMapping[] = {
    "3.0"
};

XSipSignalingFieldsImp::XSipSignalingFieldsImp(std::shared_ptr<XCommonEventHeader> header,
                const XString& correlator,
                const XString& localIpAddress,
                const XString& localPort,
                const XString& remoteIpAddress,
                const XString& remotePort,
                const XVendorNfNameFields& vendorNfNameFields):
        header_(header),
        correlator_(correlator),
        localIpAddress_(localIpAddress),
        localPort_(localPort),
        remoteIpAddress_(remoteIpAddress),
        remotePort_(remotePort),
        sipSignalingFieldsVersion_(XEnumSipSignalingFieldsSipSignalingFieldsVersion3_0),
        vendorNfNameFields_(vendorNfNameFields)
{

}

std::string XSipSignalingFieldsImp::toString()
{
    try
    {
        auto js = toJson();
        return js.dump();
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to dump XSipSignalingFields to json string:{}.", e.what());
        return "";
    }
}

void XSipSignalingFieldsImp::setRemotePort(const XString& remotePort)
{
    comVals_["remotePort"] = remotePort;
}
            
void XSipSignalingFieldsImp::setSummarySip(const XString& summarySip)
{
    comVals_["summarySip"] = summarySip;
}
            
void XSipSignalingFieldsImp::setLocalPort(const XString& localPort)
{
    comVals_["localPort"] = localPort;
}
            
void XSipSignalingFieldsImp::setAdditionalInformation(const XHashMap& additionalInformation)
{
    additionalInformation_ = additionalInformation;
}
            
void XSipSignalingFieldsImp::setLocalIpAddress(const XString& localIpAddress)
{
    comVals_["localIpAddress"] = localIpAddress;
}
            
void XSipSignalingFieldsImp::setCompressedSip(const XString& compressedSip)
{
    comVals_["compressedSip"] = compressedSip;
}
            
void XSipSignalingFieldsImp::setCorrelator(const XString& correlator)
{
    comVals_["correlator"] = correlator;
}
            
void XSipSignalingFieldsImp::setRemoteIpAddress(const XString& remoteIpAddress)
{
    comVals_["remoteIpAddress"] = remoteIpAddress;
}
            
void XSipSignalingFieldsImp::setVendorNfNameFields(const XVendorNfNameFields& vendorNfNameFields)
{
    vendorNfNameFields_ = vendorNfNameFields;
}

json XSipSignalingFieldsImp::toJson()
{
    try
    {
        json field = {
            {"sipSignalingFieldsVersion", XEnumSipSignalingFieldsSipSignalingFieldsVersionMapping[sipSignalingFieldsVersion_]},
            {"remotePort", remotePort_},
            {"localPort", localPort_},
            {"localIpAddress", localIpAddress_},
            {"correlator", correlator_},
            {"remoteIpAddress", remoteIpAddress_},
            {"vendorNfNameFields", dynamic_pointer_cast<XJsonable>(vendorNfNameFields_.imp_)->toJson()}
        };

        //optional val
        if (!additionalInformation_.empty())
        {
            field["additionalInformation"] = additionalInformation_;
        }

        field = mergeCommonValues(field, comVals_);

        json jsEvent;
        header_->setDomain(XEnumCommonEventHeaderDomainSipSignaling);
        jsEvent["event"]["commonEventHeader"] = dynamic_pointer_cast<XJsonable>(header_)->toJson();
        jsEvent["event"]["sipSignalingFields"] = field;

        return jsEvent;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XSipSignalingFields to json object:{}.", e.what());
        return json();
    }
}

std::shared_ptr<XCommonEventHeader> XSipSignalingFieldsImp::getCommonHeader()
{
    return header_;
}
            