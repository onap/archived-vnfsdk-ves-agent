#include "XVendorNfNameFields.h"
#include "XVendorNfNameFieldsImp.h"

vagt::encode::XVendorNfNameFields::XVendorNfNameFields()
{
}

vagt::encode::XVendorNfNameFields::XVendorNfNameFields(const XString & vendorName):
    imp_(make_shared<XVendorNfNameFieldsImp>(vendorName))
{
}

void vagt::encode::XVendorNfNameFields::setNfModuleName(const XString & nfModuleName)
{
    return imp_->setNfModuleName(nfModuleName);
}

void vagt::encode::XVendorNfNameFields::setNfName(const XString & nfName)
{
    return imp_->setNfName(nfName);
}

void vagt::encode::XVendorNfNameFields::setVendorName(const XString & vendorName)
{
    return imp_->setVendorName(vendorName);
}
