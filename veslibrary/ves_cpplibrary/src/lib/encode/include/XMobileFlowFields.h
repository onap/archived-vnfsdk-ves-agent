#pragma once
        
#include "XCommonEventHeader.h"
#include "XGtpPerFlowMetrics.h"

namespace vagt
{
    namespace encode
    {
        enum XEnumMobileFlowFieldsMobileFlowFieldsVersion
        {
            XEnumMobileFlowFieldsMobileFlowFieldsVersion4_0,
        };

        class XMobileFlowFields : public XExtendEvent
        {
        public:
            virtual std::string toString() = 0;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() = 0;

            virtual void setRac(const XString& rac) = 0;
            virtual void setSac(const XString& sac) = 0;
            virtual void setSamplingAlgorithm(XInteger samplingAlgorithm) = 0;
            virtual void setIpVersion(const XString& ipVersion) = 0;
            virtual void setGtpPerFlowMetrics(const XGtpPerFlowMetrics& gtpPerFlowMetrics) = 0;
            virtual void setTac(const XString& tac) = 0;
            virtual void setMnc(const XString& mnc) = 0;
            virtual void setTunnelId(const XString& tunnelId) = 0;
            virtual void setAppProtocolVersion(const XString& appProtocolVersion) = 0;
            virtual void setGtpVersion(const XString& gtpVersion) = 0;
            virtual void setConnectionType(const XString& connectionType) = 0;
            virtual void setAdditionalFields(const XHashMap& additionalFields) = 0;
            virtual void setHttpHeader(const XString& httpHeader) = 0;
            virtual void setImsi(const XString& imsi) = 0;
            virtual void setApplicationType(const XString& applicationType) = 0;
            virtual void setMsisdn(const XString& msisdn) = 0;
            virtual void setMcc(const XString& mcc) = 0;
            virtual void setFlowDirection(const XString& flowDirection) = 0;
            virtual void setLac(const XString& lac) = 0;
            virtual void setOtherEndpointPort(XInteger otherEndpointPort) = 0;
            virtual void setVlanId(const XString& vlanId) = 0;
            virtual void setImei(const XString& imei) = 0;
            virtual void setGtpProtocolType(const XString& gtpProtocolType) = 0;
            virtual void setEcgi(const XString& ecgi) = 0;
            virtual void setCid(const XString& cid) = 0;
            virtual void setReportingEndpointPort(XInteger reportingEndpointPort) = 0;
            virtual void setRadioAccessTechnology(const XString& radioAccessTechnology) = 0;
            virtual void setAppProtocolType(const XString& appProtocolType) = 0;
            virtual void setOtherEndpointIpAddress(const XString& otherEndpointIpAddress) = 0;
            virtual void setIpProtocolType(const XString& ipProtocolType) = 0;
            virtual void setOtherFunctionalRole(const XString& otherFunctionalRole) = 0;
            virtual void setReportingEndpointIpAddr(const XString& reportingEndpointIpAddr) = 0;

            static std::shared_ptr<XMobileFlowFields> create(std::shared_ptr<XCommonEventHeader> header,
                const XString& flowDirection,
                const XGtpPerFlowMetrics& gtpPerFlowMetrics,
                const XString& ipProtocolType,
                const XString& ipVersion,
                const XString& otherEndpointIpAddress,
                XInteger otherEndpointPort,
                const XString& reportingEndpointIpAddr,
                XInteger reportingEndpointPort);
        };
    }
}
        