#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XHugePages 
        {
        public:
            XHugePages(const XString& hugePagesIdentifier);

            virtual void setBytesUsed(XNumber bytesUsed);
            virtual void setHugePagesIdentifier(const XString& hugePagesIdentifier);
            virtual void setVmPageNumberFree(XNumber vmPageNumberFree);
            virtual void setBytesFree(XNumber bytesFree);
            virtual void setPercentFree(XNumber percentFree);
            virtual void setPercentUsed(XNumber percentUsed);
            virtual void setVmPageNumberUsed(XNumber vmPageNumberUsed);

            std::shared_ptr<XHugePages> imp_;

        protected:
            XHugePages();
        };

        using XArrayOfXHugePages = std::vector<XHugePages>;
    }
}
        