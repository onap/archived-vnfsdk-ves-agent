#include "XCodecsInUseImp.h"

XCodecsInUseImp::XCodecsInUseImp(const XString& codecIdentifier,
    XInteger numberInUse):
        codecIdentifier_(codecIdentifier),
        numberInUse_(numberInUse)
{

}

void XCodecsInUseImp::setCodecIdentifier(const XString& codecIdentifier)
{
    comVals_["codecIdentifier"] = codecIdentifier;
}
            
void XCodecsInUseImp::setNumberInUse(XInteger numberInUse)
{
    comVals_["numberInUse"] = numberInUse;
}

json XCodecsInUseImp::toJson()
{
    try
    {
        json field = {
            {"codecIdentifier", codecIdentifier_},
            {"numberInUse", numberInUse_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XCodecsInUse to json object:{}.", e.what());
        return json();
    }
}
            