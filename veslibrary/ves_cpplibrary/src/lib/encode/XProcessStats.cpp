#include "XProcessStats.h"
#include "XProcessStatsImp.h"

vagt::encode::XProcessStats::XProcessStats()
{
}

vagt::encode::XProcessStats::XProcessStats(const XString & processIdentifier):
    imp_(make_shared<XProcessStatsImp>(processIdentifier))
{
}

void vagt::encode::XProcessStats::setForkRate(XNumber forkRate)
{
    return imp_->setForkRate(forkRate);
}

void vagt::encode::XProcessStats::setPsStateStopped(XNumber psStateStopped)
{
    return imp_->setPsStateStopped(psStateStopped);
}

void vagt::encode::XProcessStats::setPsStatePaging(XNumber psStatePaging)
{
    return imp_->setPsStatePaging(psStatePaging);
}

void vagt::encode::XProcessStats::setPsStateSleeping(XNumber psStateSleeping)
{
    return imp_->setPsStateSleeping(psStateSleeping);
}

void vagt::encode::XProcessStats::setProcessIdentifier(const XString & processIdentifier)
{
    return imp_->setProcessIdentifier(processIdentifier);
}

void vagt::encode::XProcessStats::setPsStateBlocked(XNumber psStateBlocked)
{
    return imp_->setPsStateBlocked(psStateBlocked);
}

void vagt::encode::XProcessStats::setPsStateZombie(XNumber psStateZombie)
{
    return imp_->setPsStateZombie(psStateZombie);
}

void vagt::encode::XProcessStats::setPsStateRunning(XNumber psStateRunning)
{
    return imp_->setPsStateRunning(psStateRunning);
}
