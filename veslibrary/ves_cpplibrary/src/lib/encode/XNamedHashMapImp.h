#pragma once
        
#include "XNamedHashMap.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XNamedHashMapImp : public XNamedHashMap, public XJsonable
        {
        public:
            XNamedHashMapImp(const XString& name,
                const XHashMap& hashMap);

            virtual json toJson() override;

            virtual void setName(const XString& name) override;
            virtual void setHashMap(const XHashMap& hashMap) override;

        private:
            //required
            XString name_;
            XHashMap hashMap_;

            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        