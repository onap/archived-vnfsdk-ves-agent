#pragma once
        
#include "XEvent.h"
#include "XJsonObjectInstance.h"

namespace vagt
{
    namespace encode
    {
        class XJsonObject 
        {
        public:
            XJsonObject(const XString& objectName,
                const XArrayOfXJsonObjectInstance& objectInstances
                );

            virtual void setObjectSchema(const XString& objectSchema);
            virtual void setObjectName(const XString& objectName);
            virtual void setNfSubscriptionId(const XString& nfSubscriptionId);
            virtual void setObjectInstances(const XArrayOfXJsonObjectInstance& objectInstances);
            virtual void setNfSubscribedObjectName(const XString& nfSubscribedObjectName);
            virtual void setObjectSchemaUrl(const XString& objectSchemaUrl);

            std::shared_ptr<XJsonObject> imp_;
        protected:
            XJsonObject();
        };

        using XArrayOfJsonObject = std::vector<XJsonObject>;
    }
}
        