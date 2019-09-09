#pragma once
        
#include "XCommonEventHeader.h"
#include "XJsonObject.h"
#include "XNamedHashMap.h"

namespace vagt
{
    namespace encode
    {
        enum XEnumOtherFieldsOtherFieldsVersion
        {
            XEnumOtherFieldsOtherFieldsVersion3_0,
        };

        class XOtherFields : public XExtendEvent
        {
        public:
            virtual std::string toString() = 0;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() = 0;

            virtual void setJsonObjects(const XArrayOfJsonObject& jsonObjects) = 0;
            virtual void setArrayOfNamedHashMap(const XArrayOfNamedHashMap& arrayOfNamedHashMap) = 0;
            virtual void setHashMap(const XHashMap& hashMap) = 0;

            static std::shared_ptr<XOtherFields> create(std::shared_ptr<XCommonEventHeader> header);
        };
    }
}
        