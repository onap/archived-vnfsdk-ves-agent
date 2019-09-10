#include "XMobileFlowFieldsImp.h"

const std::string XEnumMobileFlowFieldsMobileFlowFieldsVersionMapping[] = {
    "4.0"
};

XMobileFlowFieldsImp::XMobileFlowFieldsImp(std::shared_ptr<XCommonEventHeader> header,
                const XString& flowDirection,
                const XGtpPerFlowMetrics& gtpPerFlowMetrics,
                const XString& ipProtocolType,
                const XString& ipVersion,
                const XString& otherEndpointIpAddress,
                XInteger otherEndpointPort,
                const XString& reportingEndpointIpAddr,
                XInteger reportingEndpointPort
    ):
        header_(header),
        flowDirection_(flowDirection),
        gtpPerFlowMetrics_(gtpPerFlowMetrics),
        ipProtocolType_(ipProtocolType),
        ipVersion_(ipVersion),
        mobileFlowFieldsVersion_(XEnumMobileFlowFieldsMobileFlowFieldsVersion4_0),
        otherEndpointIpAddress_(otherEndpointIpAddress),
        otherEndpointPort_(otherEndpointPort),
        reportingEndpointIpAddr_(reportingEndpointIpAddr),
        reportingEndpointPort_(reportingEndpointPort)
{

}

std::string XMobileFlowFieldsImp::toString()
{
    try
    {
        auto js = toJson();
        return js.dump();
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to dump XMobileFlowFields to json string:{}.", e.what());
        return "";
    }
}

void XMobileFlowFieldsImp::setRac(const XString& rac)
{
    comVals_["rac"] = rac;
}
            
void XMobileFlowFieldsImp::setSac(const XString& sac)
{
    comVals_["sac"] = sac;
}
            
void XMobileFlowFieldsImp::setSamplingAlgorithm(XInteger samplingAlgorithm)
{
    comVals_["samplingAlgorithm"] = samplingAlgorithm;
}
            
void XMobileFlowFieldsImp::setIpVersion(const XString& ipVersion)
{
    comVals_["ipVersion"] = ipVersion;
}
            
void XMobileFlowFieldsImp::setGtpPerFlowMetrics(const XGtpPerFlowMetrics& gtpPerFlowMetrics)
{
    gtpPerFlowMetrics_ = gtpPerFlowMetrics;
}
            
void XMobileFlowFieldsImp::setTac(const XString& tac)
{
    comVals_["tac"] = tac;
}
            
void XMobileFlowFieldsImp::setMnc(const XString& mnc)
{
    comVals_["mnc"] = mnc;
}
            
void XMobileFlowFieldsImp::setTunnelId(const XString& tunnelId)
{
    comVals_["tunnelId"] = tunnelId;
}
            
void XMobileFlowFieldsImp::setAppProtocolVersion(const XString& appProtocolVersion)
{
    comVals_["appProtocolVersion"] = appProtocolVersion;
}
            
void XMobileFlowFieldsImp::setGtpVersion(const XString& gtpVersion)
{
    comVals_["gtpVersion"] = gtpVersion;
}
            
void XMobileFlowFieldsImp::setConnectionType(const XString& connectionType)
{
    comVals_["connectionType"] = connectionType;
}
            
void XMobileFlowFieldsImp::setAdditionalFields(const XHashMap& additionalFields)
{
    additionalFields_ = additionalFields;
}
            
void XMobileFlowFieldsImp::setHttpHeader(const XString& httpHeader)
{
    comVals_["httpHeader"] = httpHeader;
}
            
void XMobileFlowFieldsImp::setImsi(const XString& imsi)
{
    comVals_["imsi"] = imsi;
}
            
void XMobileFlowFieldsImp::setApplicationType(const XString& applicationType)
{
    comVals_["applicationType"] = applicationType;
}
            
void XMobileFlowFieldsImp::setMsisdn(const XString& msisdn)
{
    comVals_["msisdn"] = msisdn;
}
            
void XMobileFlowFieldsImp::setMcc(const XString& mcc)
{
    comVals_["mcc"] = mcc;
}
            
void XMobileFlowFieldsImp::setFlowDirection(const XString& flowDirection)
{
    comVals_["flowDirection"] = flowDirection;
}
            
void XMobileFlowFieldsImp::setLac(const XString& lac)
{
    comVals_["lac"] = lac;
}
            
void XMobileFlowFieldsImp::setOtherEndpointPort(XInteger otherEndpointPort)
{
    comVals_["otherEndpointPort"] = otherEndpointPort;
}
            
void XMobileFlowFieldsImp::setVlanId(const XString& vlanId)
{
    comVals_["vlanId"] = vlanId;
}
            
void XMobileFlowFieldsImp::setImei(const XString& imei)
{
    comVals_["imei"] = imei;
}
            
void XMobileFlowFieldsImp::setGtpProtocolType(const XString& gtpProtocolType)
{
    comVals_["gtpProtocolType"] = gtpProtocolType;
}
            
void XMobileFlowFieldsImp::setEcgi(const XString& ecgi)
{
    comVals_["ecgi"] = ecgi;
}
            
void XMobileFlowFieldsImp::setCid(const XString& cid)
{
    comVals_["cid"] = cid;
}
            
void XMobileFlowFieldsImp::setReportingEndpointPort(XInteger reportingEndpointPort)
{
    comVals_["reportingEndpointPort"] = reportingEndpointPort;
}
            
void XMobileFlowFieldsImp::setRadioAccessTechnology(const XString& radioAccessTechnology)
{
    comVals_["radioAccessTechnology"] = radioAccessTechnology;
}
            
void XMobileFlowFieldsImp::setAppProtocolType(const XString& appProtocolType)
{
    comVals_["appProtocolType"] = appProtocolType;
}
            
void XMobileFlowFieldsImp::setOtherEndpointIpAddress(const XString& otherEndpointIpAddress)
{
    comVals_["otherEndpointIpAddress"] = otherEndpointIpAddress;
}
            
void XMobileFlowFieldsImp::setIpProtocolType(const XString& ipProtocolType)
{
    comVals_["ipProtocolType"] = ipProtocolType;
}
            
void XMobileFlowFieldsImp::setOtherFunctionalRole(const XString& otherFunctionalRole)
{
    comVals_["otherFunctionalRole"] = otherFunctionalRole;
}
            
void XMobileFlowFieldsImp::setReportingEndpointIpAddr(const XString& reportingEndpointIpAddr)
{
    comVals_["reportingEndpointIpAddr"] = reportingEndpointIpAddr;
}

json XMobileFlowFieldsImp::toJson()
{
    try
    {
        json field = {
            {"ipVersion", ipVersion_},
            {"mobileFlowFieldsVersion", XEnumMobileFlowFieldsMobileFlowFieldsVersionMapping[mobileFlowFieldsVersion_]},
            {"gtpPerFlowMetrics", dynamic_pointer_cast<XJsonable>(gtpPerFlowMetrics_.imp_)->toJson()},
            {"flowDirection", flowDirection_},
            {"otherEndpointPort", otherEndpointPort_},
            {"reportingEndpointPort", reportingEndpointPort_},
            {"otherEndpointIpAddress", otherEndpointIpAddress_},
            {"ipProtocolType", ipProtocolType_},
            {"reportingEndpointIpAddr", reportingEndpointIpAddr_}
        };

        //optional val
        if (!additionalFields_.empty())
        {
            field["additionalFields"] = additionalFields_;
        }
        field = mergeCommonValues(field, comVals_);

        json jsEvent;
        header_->setDomain(XEnumCommonEventHeaderDomainMobileFlow);
        jsEvent["event"]["commonEventHeader"] = dynamic_pointer_cast<XJsonable>(header_)->toJson();
        jsEvent["event"]["mobileFlowFields"] = field;

        return jsEvent;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XMobileFlowFields to json object:{}.", e.what());
        return json();
    }
}

std::shared_ptr<XCommonEventHeader> XMobileFlowFieldsImp::getCommonHeader()
{
    return header_;
}
            