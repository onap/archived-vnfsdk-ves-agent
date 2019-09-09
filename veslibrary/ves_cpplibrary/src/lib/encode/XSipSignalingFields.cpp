#include "XSipSignalingFields.h"
#include "XSipSignalingFieldsImp.h"

std::shared_ptr<XSipSignalingFields> vagt::encode::XSipSignalingFields::create(std::shared_ptr<XCommonEventHeader> header, const XString & correlator, const XString & localIpAddress, const XString & localPort, const XString & remoteIpAddress, const XString & remotePort, const XVendorNfNameFields & vendorNfNameFields)
{
    return std::make_shared<XSipSignalingFieldsImp>(header,
                correlator,
                localIpAddress,
                localPort,
                remoteIpAddress,
                remotePort,
                vendorNfNameFields);
}
