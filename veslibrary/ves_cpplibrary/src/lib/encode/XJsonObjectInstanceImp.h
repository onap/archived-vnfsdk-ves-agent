#pragma once
        
#include "XJsonObjectInstance.h"
#include "XInternal.h"
#include "XJsonObject.h"

namespace vagt
{
    namespace encode
    {
        class XJsonObjectInstanceImp : public XJsonObjectInstance, public XJsonable
        {
        public:
            XJsonObjectInstanceImp();

            virtual json toJson() override;

            virtual void setJsonObject(const XJsonObject& jsonObject) override;
            virtual void setObjectInstance(const XString& objectInstance) override;
            virtual void setObjectInstanceEpochMicrosec(XNumber objectInstanceEpochMicrosec) override;
            virtual void setObjectKeys(const XArrayOfXKey& objectKeys) override;

        private:
            //optional
            XString objectInstance_;
            std::shared_ptr<XJsonObject> jsonObject_;
            XArrayOfXKey objectKeys_;
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        