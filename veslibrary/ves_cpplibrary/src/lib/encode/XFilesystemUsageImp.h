#pragma once
        
#include "XFilesystemUsage.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XFilesystemUsageImp : public XFilesystemUsage, public XJsonable
        {
        public:
            XFilesystemUsageImp(const XString& filesystemName,
                XNumber blockConfigured,
                XNumber blockIops,
                XNumber blockUsed,
                XNumber ephemeralConfigured,
                XNumber ephemeralIops,
                XNumber ephemeralUsed
                );

            virtual json toJson() override;

            virtual void setBlockConfigured(XNumber blockConfigured) override;
            virtual void setBlockUsed(XNumber blockUsed) override;
            virtual void setEphemeralConfigured(XNumber ephemeralConfigured) override;
            virtual void setEphemeralIops(XNumber ephemeralIops) override;
            virtual void setFilesystemName(const XString& filesystemName) override;
            virtual void setBlockIops(XNumber blockIops) override;
            virtual void setEphemeralUsed(XNumber ephemeralUsed) override;

        private:
            //required
            XNumber blockConfigured_;
            XNumber blockUsed_;
            XNumber ephemeralConfigured_;
            XNumber ephemeralIops_;
            XString filesystemName_;
            XNumber blockIops_;
            XNumber ephemeralUsed_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        