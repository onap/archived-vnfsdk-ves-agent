#pragma once
        
#include "XMobileFlowFields.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XMobileFlowFieldsImp : public XMobileFlowFields, public XJsonable
        {
        public:
            XMobileFlowFieldsImp(std::shared_ptr<XCommonEventHeader> header,
                const XString& flowDirection,
                const XGtpPerFlowMetrics& gtpPerFlowMetrics,
                const XString& ipProtocolType,
                const XString& ipVersion,
                const XString& otherEndpointIpAddress,
                XInteger otherEndpointPort,
                const XString& reportingEndpointIpAddr,
                XInteger reportingEndpointPort);

            virtual std::string toString() override;

            virtual json toJson() override;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() override;

            virtual void setRac(const XString& rac) override;
            virtual void setSac(const XString& sac) override;
            virtual void setSamplingAlgorithm(XInteger samplingAlgorithm) override;
            virtual void setIpVersion(const XString& ipVersion) override;
            virtual void setGtpPerFlowMetrics(const XGtpPerFlowMetrics& gtpPerFlowMetrics) override;
            virtual void setTac(const XString& tac) override;
            virtual void setMnc(const XString& mnc) override;
            virtual void setTunnelId(const XString& tunnelId) override;
            virtual void setAppProtocolVersion(const XString& appProtocolVersion) override;
            virtual void setGtpVersion(const XString& gtpVersion) override;
            virtual void setConnectionType(const XString& connectionType) override;
            virtual void setAdditionalFields(const XHashMap& additionalFields) override;
            virtual void setHttpHeader(const XString& httpHeader) override;
            virtual void setImsi(const XString& imsi) override;
            virtual void setApplicationType(const XString& applicationType) override;
            virtual void setMsisdn(const XString& msisdn) override;
            virtual void setMcc(const XString& mcc) override;
            virtual void setFlowDirection(const XString& flowDirection) override;
            virtual void setLac(const XString& lac) override;
            virtual void setOtherEndpointPort(XInteger otherEndpointPort) override;
            virtual void setVlanId(const XString& vlanId) override;
            virtual void setImei(const XString& imei) override;
            virtual void setGtpProtocolType(const XString& gtpProtocolType) override;
            virtual void setEcgi(const XString& ecgi) override;
            virtual void setCid(const XString& cid) override;
            virtual void setReportingEndpointPort(XInteger reportingEndpointPort) override;
            virtual void setRadioAccessTechnology(const XString& radioAccessTechnology) override;
            virtual void setAppProtocolType(const XString& appProtocolType) override;
            virtual void setOtherEndpointIpAddress(const XString& otherEndpointIpAddress) override;
            virtual void setIpProtocolType(const XString& ipProtocolType) override;
            virtual void setOtherFunctionalRole(const XString& otherFunctionalRole) override;
            virtual void setReportingEndpointIpAddr(const XString& reportingEndpointIpAddr) override;

        private:
            //required
            std::shared_ptr<XCommonEventHeader> header_;
            XString ipVersion_;
            XEnumMobileFlowFieldsMobileFlowFieldsVersion mobileFlowFieldsVersion_;
            XGtpPerFlowMetrics gtpPerFlowMetrics_;
            XString flowDirection_;
            XInteger otherEndpointPort_;
            XInteger reportingEndpointPort_;
            XString otherEndpointIpAddress_;
            XString ipProtocolType_;
            XString reportingEndpointIpAddr_;
            //optional
            XHashMap additionalFields_;
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        