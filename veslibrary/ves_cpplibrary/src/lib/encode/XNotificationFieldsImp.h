#pragma once
        
#include "XNotificationFields.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XNotificationFieldsImp : public XNotificationFields, public XJsonable
        {
        public:
            XNotificationFieldsImp(std::shared_ptr<XCommonEventHeader> header,
                const XString& changeIdentifier,
                const XString& changeType
                );

            virtual std::string toString() override;

            virtual json toJson() override;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() override;

            virtual void setNewState(const XString& newState) override;
            virtual void setChangeType(const XString& changeType) override;
            virtual void setArrayOfNamedHashMap(const XArrayOfNamedHashMap& arrayOfNamedHashMap) override;
            virtual void setChangeContact(const XString& changeContact) override;
            virtual void setChangeIdentifier(const XString& changeIdentifier) override;
            virtual void setAdditionalFields(const XHashMap& additionalFields) override;
            virtual void setOldState(const XString& oldState) override;
            virtual void setStateInterface(const XString& stateInterface) override;

        private:
            //required
            std::shared_ptr<XCommonEventHeader> header_;
            XEnumNotificationFieldsNotificationFieldsVersion notificationFieldsVersion_;
            XString changeType_;
            XString changeIdentifier_;
            //optional
            XArrayOfNamedHashMap arrayOfNamedHashMap_;
            XHashMap additionalFields_;
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        