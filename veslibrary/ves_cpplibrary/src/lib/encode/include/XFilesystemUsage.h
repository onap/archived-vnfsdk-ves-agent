#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XFilesystemUsage 
        {
        public:
            XFilesystemUsage(const XString& filesystemName,
                XNumber blockConfigured,
                XNumber blockIops,
                XNumber blockUsed,
                XNumber ephemeralConfigured,
                XNumber ephemeralIops,
                XNumber ephemeralUsed
                );

            virtual void setBlockConfigured(XNumber blockConfigured);
            virtual void setBlockUsed(XNumber blockUsed);
            virtual void setEphemeralConfigured(XNumber ephemeralConfigured);
            virtual void setEphemeralIops(XNumber ephemeralIops);
            virtual void setFilesystemName(const XString& filesystemName);
            virtual void setBlockIops(XNumber blockIops);
            virtual void setEphemeralUsed(XNumber ephemeralUsed);

            std::shared_ptr<XFilesystemUsage> imp_;

        protected:
            XFilesystemUsage();
        };

        using XArrayOfXFilesystemUsage = std::vector<XFilesystemUsage>;
    }
}
        