#include "XCounter.h"
#include "XCounterImp.h"

vagt::encode::XCounter::XCounter()
{
}

vagt::encode::XCounter::XCounter(XEnumCounterCriticality criticality, const XHashMap & hashMap, const XString & thresholdCrossed):
    imp_(make_shared<XCounterImp>(criticality, hashMap, thresholdCrossed))
{
}

void vagt::encode::XCounter::setThresholdCrossed(const XString & thresholdCrossed)
{
    return imp_->setThresholdCrossed(thresholdCrossed);
}

void vagt::encode::XCounter::setHashMap(const XHashMap & hashMap)
{
    return imp_->setHashMap(hashMap);
}

void vagt::encode::XCounter::setCriticality(XEnumCounterCriticality criticality)
{
    return imp_->setCriticality(criticality);
}
