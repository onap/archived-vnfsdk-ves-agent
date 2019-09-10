#include "XLoadImp.h"

XLoadImp::XLoadImp():XLoad(nullptr)
{

}

void XLoadImp::setShortTerm(XNumber shortTerm)
{
    comVals_["shortTerm"] = shortTerm;
}
            
void XLoadImp::setLongTerm(XNumber longTerm)
{
    comVals_["longTerm"] = longTerm;
}
            
void XLoadImp::setMidTerm(XNumber midTerm)
{
    comVals_["midTerm"] = midTerm;
}

json XLoadImp::toJson()
{
    try
    {
        json field;

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XLoad to json object:{}.", e.what());
        return json();
    }
}
            