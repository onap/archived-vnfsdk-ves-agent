#pragma once
        
#include "XOtherFields.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XOtherFieldsImp : public XOtherFields, public XJsonable
        {
        public:
            XOtherFieldsImp(std::shared_ptr<XCommonEventHeader> header);

            virtual std::string toString() override;

            virtual json toJson() override;

            virtual std::shared_ptr<XCommonEventHeader> getCommonHeader() override;

            virtual void setJsonObjects(const XArrayOfJsonObject& jsonObjects) override;
            virtual void setArrayOfNamedHashMap(const XArrayOfNamedHashMap& arrayOfNamedHashMap) override;
            virtual void setHashMap(const XHashMap& hashMap) override;

        private:
            //required
            std::shared_ptr<XCommonEventHeader> header_;
            XEnumOtherFieldsOtherFieldsVersion otherFieldsVersion_;
            //optional
            XArrayOfJsonObject jsonObjects_;
            XArrayOfNamedHashMap arrayOfNamedHashMap_;
            XHashMap hashMap_;
        };
    }
}
        