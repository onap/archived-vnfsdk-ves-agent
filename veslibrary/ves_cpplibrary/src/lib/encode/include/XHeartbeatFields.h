#pragma once
        
#include "XCommonEventHeader.h"

namespace vagt
{
    namespace encode
    {
        enum XEnumHeartbeatFieldsHeartbeatFieldsVersion
        {
            XEnumHeartbeatFieldsHeartbeatFieldsVersion3_0,
        };

        class XHeartbeatFields : public XExtendEvent
        {
        public:
            virtual std::string toString() = 0;
            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() = 0;

            virtual void setHeartbeatInterval(XInteger heartbeatInterval) = 0;
            virtual void setAdditionalFields(const XHashMap& additionalFields) = 0;

            static std::shared_ptr<XHeartbeatFields> create(std::shared_ptr<XCommonEventHeader> header, XInteger heartbeatInterval);
        };
    }
}
        
