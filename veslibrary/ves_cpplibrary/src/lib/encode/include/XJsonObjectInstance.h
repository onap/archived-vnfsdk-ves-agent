#pragma once
        
#include "XEvent.h"
#include "XKey.h"

namespace vagt
{
    namespace encode
    {
        class XJsonObject;
        class XJsonObjectInstance
        {
        public:
            XJsonObjectInstance();

            virtual void setJsonObject(const XJsonObject& jsonObject);
            virtual void setObjectInstance(const XString& objectInstance);
            virtual void setObjectInstanceEpochMicrosec(XNumber objectInstanceEpochMicrosec);
            virtual void setObjectKeys(const XArrayOfXKey& objectKeys);

            std::shared_ptr<XJsonObjectInstance> imp_;

        protected:
            XJsonObjectInstance(void*);
        };
        using XArrayOfXJsonObjectInstance = std::vector<XJsonObjectInstance>;
    }
}
        