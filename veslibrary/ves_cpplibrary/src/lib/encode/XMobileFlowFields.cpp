#include "XMobileFlowFields.h"
#include "XMobileFlowFieldsImp.h"

std::shared_ptr<XMobileFlowFields> vagt::encode::XMobileFlowFields::create(std::shared_ptr<XCommonEventHeader> header, const XString & flowDirection, const XGtpPerFlowMetrics & gtpPerFlowMetrics, const XString & ipProtocolType, const XString & ipVersion, const XString & otherEndpointIpAddress, XInteger otherEndpointPort, const XString & reportingEndpointIpAddr, XInteger reportingEndpointPort)
{
    return std::make_shared<XMobileFlowFieldsImp>(header,
                flowDirection,
                gtpPerFlowMetrics,
                ipProtocolType,
                ipVersion,
                otherEndpointIpAddress,
                otherEndpointPort,
                reportingEndpointIpAddr,
                reportingEndpointPort);
}
