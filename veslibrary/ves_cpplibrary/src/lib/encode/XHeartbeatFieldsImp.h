#pragma once
        
#include "XHeartbeatFields.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XHeartbeatFieldsImp : public XHeartbeatFields, public XJsonable
        {
        public:
            XHeartbeatFieldsImp(std::shared_ptr<XCommonEventHeader> header, XInteger heartbeatInterval);

            virtual std::string toString() override;
            virtual json toJson() override;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() override;

            virtual void setHeartbeatInterval(XInteger heartbeatInterval) override;
            virtual void setAdditionalFields(const XHashMap& additionalFields) override;

        private:
            //required
            std::shared_ptr<XCommonEventHeader> header_;
            XInteger heartbeatInterval_;
            XEnumHeartbeatFieldsHeartbeatFieldsVersion heartbeatFieldsVersion_;
            //optional
            XHashMap additionalFields_;
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        
