#pragma once
        
#include "XCommonEventHeader.h"
#include "XNamedHashMap.h"

namespace vagt
{
    namespace encode
    {
        enum XEnumNotificationFieldsNotificationFieldsVersion
        {
            XEnumNotificationFieldsNotificationFieldsVersion2_0,
        };

        class XNotificationFields : public XExtendEvent
        {
        public:
            virtual std::string toString() = 0;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() = 0;

            virtual void setNewState(const XString& newState) = 0;
            virtual void setChangeType(const XString& changeType) = 0;
            virtual void setArrayOfNamedHashMap(const XArrayOfNamedHashMap& arrayOfNamedHashMap) = 0;
            virtual void setChangeContact(const XString& changeContact) = 0;
            virtual void setChangeIdentifier(const XString& changeIdentifier) = 0;
            virtual void setAdditionalFields(const XHashMap& additionalFields) = 0;
            virtual void setOldState(const XString& oldState) = 0;
            virtual void setStateInterface(const XString& stateInterface) = 0;

            static std::shared_ptr<XNotificationFields> create(std::shared_ptr<XCommonEventHeader> header,
                const XString& changeIdentifier,
                const XString& changeType
                );
        };
    }
}
        