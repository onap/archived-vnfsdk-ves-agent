#pragma once

#include "XProcessStats.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XProcessStatsImp : public XProcessStats, public XJsonable
        {
        public:
            XProcessStatsImp(const XString& processIdentifier);

            virtual json toJson() override;

            virtual void setForkRate(XNumber forkRate) override;
            virtual void setPsStateStopped(XNumber psStateStopped) override;
            virtual void setPsStatePaging(XNumber psStatePaging) override;
            virtual void setPsStateSleeping(XNumber psStateSleeping) override;
            virtual void setProcessIdentifier(const XString& processIdentifier) override;
            virtual void setPsStateBlocked(XNumber psStateBlocked) override;
            virtual void setPsStateZombie(XNumber psStateZombie) override;
            virtual void setPsStateRunning(XNumber psStateRunning) override;

        private:
            //required
            XString processIdentifier_;
            //optional
            std::map<std::string, XCommonValue> comVals_;
        };
    }
}
        