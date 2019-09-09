#pragma once
        
#include "XHugePages.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XHugePagesImp : public XHugePages, public XJsonable
        {
        public:
            XHugePagesImp(const XString& hugePagesIdentifier);

            virtual json toJson() override;

            void setBytesUsed(XNumber bytesUsed);
            void setHugePagesIdentifier(const XString& hugePagesIdentifier);
            void setVmPageNumberFree(XNumber vmPageNumberFree);
            void setBytesFree(XNumber bytesFree);
            void setPercentFree(XNumber percentFree);
            void setPercentUsed(XNumber percentUsed);
            void setVmPageNumberUsed(XNumber vmPageNumberUsed);

        private:
            //required
            XString hugePagesIdentifier_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        