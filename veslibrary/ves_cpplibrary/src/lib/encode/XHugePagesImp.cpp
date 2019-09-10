#include "XHugePagesImp.h"

XHugePagesImp::XHugePagesImp(const XString& hugePagesIdentifier):
        hugePagesIdentifier_(hugePagesIdentifier)
{

}

void XHugePagesImp::setBytesUsed(XNumber bytesUsed)
{
    comVals_["bytesUsed"] = bytesUsed;
}
            
void XHugePagesImp::setHugePagesIdentifier(const XString& hugePagesIdentifier)
{
    comVals_["hugePagesIdentifier"] = hugePagesIdentifier;
}
            
void XHugePagesImp::setVmPageNumberFree(XNumber vmPageNumberFree)
{
    comVals_["vmPageNumberFree"] = vmPageNumberFree;
}
            
void XHugePagesImp::setBytesFree(XNumber bytesFree)
{
    comVals_["bytesFree"] = bytesFree;
}
            
void XHugePagesImp::setPercentFree(XNumber percentFree)
{
    comVals_["percentFree"] = percentFree;
}
            
void XHugePagesImp::setPercentUsed(XNumber percentUsed)
{
    comVals_["percentUsed"] = percentUsed;
}
            
void XHugePagesImp::setVmPageNumberUsed(XNumber vmPageNumberUsed)
{
    comVals_["vmPageNumberUsed"] = vmPageNumberUsed;
}

json XHugePagesImp::toJson()
{
    try
    {
        json field = {
            {"hugePagesIdentifier", hugePagesIdentifier_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XHugePages to json object:{}.", e.what());
        return json();
    }
}
            