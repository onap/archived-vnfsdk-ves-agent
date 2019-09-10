#include "XVendorNfNameFieldsImp.h"

XVendorNfNameFieldsImp::XVendorNfNameFieldsImp(const XString& vendorName):
        vendorName_(vendorName)
{

}

void XVendorNfNameFieldsImp::setNfModuleName(const XString& nfModuleName)
{
    comVals_["nfModuleName"] = nfModuleName;
}
            
void XVendorNfNameFieldsImp::setNfName(const XString& nfName)
{
    comVals_["nfName"] = nfName;
}
            
void XVendorNfNameFieldsImp::setVendorName(const XString& vendorName)
{
    comVals_["vendorName"] = vendorName;
}

json XVendorNfNameFieldsImp::toJson()
{
    try
    {
        if (vendorName_.empty())
        {
            return json();
        }

        json field = {
            {"vendorName", vendorName_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XVendorNfNameFields to json object:{}.", e.what());
        return json();
    }
}
           