#pragma once
        
#include "XEvent.h"

namespace vagt
{
    namespace encode
    {
        class XProcessStats 
        {
        public:
            XProcessStats(const XString& processIdentifier);

            virtual void setForkRate(XNumber forkRate);
            virtual void setPsStateStopped(XNumber psStateStopped);
            virtual void setPsStatePaging(XNumber psStatePaging);
            virtual void setPsStateSleeping(XNumber psStateSleeping);
            virtual void setProcessIdentifier(const XString& processIdentifier);
            virtual void setPsStateBlocked(XNumber psStateBlocked);
            virtual void setPsStateZombie(XNumber psStateZombie);
            virtual void setPsStateRunning(XNumber psStateRunning);

            std::shared_ptr<XProcessStats> imp_;

        protected:
            XProcessStats();
        };

        using XArrayOfXProcessStats = std::vector<XProcessStats>;
    }
}
        