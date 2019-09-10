#pragma once
        
#include "XThresholdCrossingAlertFields.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XThresholdCrossingAlertFieldsImp : public XThresholdCrossingAlertFields, public XJsonable
        {
        public:
            XThresholdCrossingAlertFieldsImp(std::shared_ptr<XCommonEventHeader> header,
                XEnumThresholdCrossingAlertFieldsAlertAction alertAction,
                XEnumThresholdCrossingAlertFieldsAlertType alertType,
                XEnumThresholdCrossingAlertFieldsEventSeverity eventSeverity,
                const XString& alertDescription,
                const XString& collectionTimestamp,
                const XString& eventStartTimestamp,
                const XArrayOfXCounter& additionalParameters
                );

            virtual std::string toString() override;

            virtual json toJson() override;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() override;

            virtual void setAlertDescription(const XString& alertDescription) override;
            virtual void setAlertType(XEnumThresholdCrossingAlertFieldsAlertType alertType) override;
            virtual void setInterfaceName(const XString& interfaceName) override;
            virtual void setCollectionTimestamp(const XString& collectionTimestamp) override;
            virtual void setEventSeverity(XEnumThresholdCrossingAlertFieldsEventSeverity eventSeverity) override;
            virtual void setPossibleRootCause(const XString& possibleRootCause) override;
            virtual void setAssociatedAlertIdList(const XArrayOfString& associatedAlertIdList) override;
            virtual void setAlertValue(const XString& alertValue) override;
            virtual void setDataCollector(const XString& dataCollector) override;
            virtual void setAdditionalParameters(const XArrayOfXCounter& additionalParameters) override;
            virtual void setAlertAction(XEnumThresholdCrossingAlertFieldsAlertAction alertAction) override;
            virtual void setNetworkService(const XString& networkService) override;
            virtual void setElementType(const XString& elementType) override;
            virtual void setAdditionalFields(const XHashMap& additionalFields) override;
            virtual void setEventStartTimestamp(const XString& eventStartTimestamp) override;

        private:
            //required
            std::shared_ptr<XCommonEventHeader> header_;
            XEnumThresholdCrossingAlertFieldsThresholdCrossingFieldsVersion thresholdCrossingFieldsVersion_;
            XString alertDescription_;
            XEnumThresholdCrossingAlertFieldsAlertType alertType_;
            XString collectionTimestamp_;
            XEnumThresholdCrossingAlertFieldsEventSeverity eventSeverity_;
            XArrayOfXCounter additionalParameters_;
            XEnumThresholdCrossingAlertFieldsAlertAction alertAction_;
            XString eventStartTimestamp_;
            //optional
            XArrayOfString associatedAlertIdList_;
            XHashMap additionalFields_;
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        