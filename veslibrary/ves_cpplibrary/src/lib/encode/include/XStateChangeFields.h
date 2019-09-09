#pragma once
        
#include "XCommonEventHeader.h"

namespace vagt
{
    namespace encode
    {
        enum XEnumStateChangeFieldsState
        {
            XEnumStateChangeFieldsStateInService,
            XEnumStateChangeFieldsStateMaintenance,
            XEnumStateChangeFieldsStateOutOfService,
        };

        enum XEnumStateChangeFieldsStateChangeFieldsVersion
        {
            XEnumStateChangeFieldsStateChangeFieldsVersion4_0,
        };

        class XStateChangeFields : public XExtendEvent
        {
        public:
            virtual std::string toString() = 0;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() = 0;

            virtual void setNewState(XEnumStateChangeFieldsState newState) = 0;
            virtual void setOldState(XEnumStateChangeFieldsState oldState) = 0;
            virtual void setAdditionalFields(const XHashMap& additionalFields) = 0;
            virtual void setStateInterface(const XString& stateInterface) = 0;

            static std::shared_ptr<XStateChangeFields> create(std::shared_ptr<XCommonEventHeader> header,
                XEnumStateChangeFieldsState newState,
                XEnumStateChangeFieldsState oldState,
                const XString& stateInterface);
        };
    }
}
        