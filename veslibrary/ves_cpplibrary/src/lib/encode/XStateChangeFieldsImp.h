#pragma once
        
#include "XStateChangeFields.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XStateChangeFieldsImp : public XStateChangeFields, public XJsonable
        {
        public:
            XStateChangeFieldsImp(std::shared_ptr<XCommonEventHeader> header,
                XEnumStateChangeFieldsState newState,
                XEnumStateChangeFieldsState oldState,
                const XString& stateInterface);

            virtual std::string toString() override;

            virtual json toJson() override;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() override;

            virtual void setNewState(XEnumStateChangeFieldsState newState) override;
            virtual void setOldState(XEnumStateChangeFieldsState oldState) override;
            virtual void setAdditionalFields(const XHashMap& additionalFields) override;
            virtual void setStateInterface(const XString& stateInterface) override;

        private:
            //required
            std::shared_ptr<XCommonEventHeader> header_;
            XEnumStateChangeFieldsStateChangeFieldsVersion stateChangeFieldsVersion_;
            XEnumStateChangeFieldsState newState_;
            XEnumStateChangeFieldsState oldState_;
            XString stateInterface_;
            //optional
            XHashMap additionalFields_;
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        