#include "XCounterImp.h"

const std::string XEnumCounterCriticalityMapping[] = {
    "CRIT",
    "MAJ"
};

XCounterImp::XCounterImp(XEnumCounterCriticality criticality,
    const XHashMap& hashMap,
    const XString& thresholdCrossed) :
    criticality_(criticality),
    hashMap_(hashMap),
    thresholdCrossed_(thresholdCrossed)
{

}

void XCounterImp::setThresholdCrossed(const XString& thresholdCrossed)
{
    comVals_["thresholdCrossed"] = thresholdCrossed;
}

void XCounterImp::setHashMap(const XHashMap& hashMap)
{
    hashMap_ = hashMap;
}

void XCounterImp::setCriticality(XEnumCounterCriticality criticality)
{
    auto val = XEnumCounterCriticalityMapping[criticality];
    comVals_["criticality"] = val;
}

json XCounterImp::toJson()
{
    try
    {
        json field = {
            { "thresholdCrossed", thresholdCrossed_ },
            { "hashMap", hashMap_ },
            { "criticality", XEnumCounterCriticalityMapping[criticality_] }
        };

        //optional val

        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XCounter to json object:{}.", e.what());
        return json();
    }
}