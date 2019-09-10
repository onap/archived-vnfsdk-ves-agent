#pragma once
        
#include "XJsonObject.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XJsonObjectImp : public XJsonObject, public XJsonable
        {
        public:
            XJsonObjectImp(const XString& objectName,
                const XArrayOfXJsonObjectInstance& objectInstances
                );

            virtual json toJson() override;

            virtual void setObjectSchema(const XString& objectSchema) override;
            virtual void setObjectName(const XString& objectName) override;
            virtual void setNfSubscriptionId(const XString& nfSubscriptionId) override;
            virtual void setObjectInstances(const XArrayOfXJsonObjectInstance& objectInstances) override;
            virtual void setNfSubscribedObjectName(const XString& nfSubscribedObjectName) override;
            virtual void setObjectSchemaUrl(const XString& objectSchemaUrl) override;

        private:
            //required
            XString objectName_;
            XArrayOfXJsonObjectInstance objectInstances_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        