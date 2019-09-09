#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XNamedHashMap 
        {
        public:
            XNamedHashMap(const XString& name,
                const XHashMap& hashMap);

            virtual void setName(const XString& name);
            virtual void setHashMap(const XHashMap& hashMap);

            std::shared_ptr<XNamedHashMap> imp_;

        protected:
            XNamedHashMap();
        };

        using XArrayOfNamedHashMap = std::vector<XNamedHashMap>;
    }
}
        