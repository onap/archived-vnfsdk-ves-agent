#include "XHugePages.h"
#include "XHugePagesImp.h"

vagt::encode::XHugePages::XHugePages()
{
}

vagt::encode::XHugePages::XHugePages(const XString & hugePagesIdentifier):
    imp_(make_shared<XHugePagesImp>(hugePagesIdentifier))
{
}

void vagt::encode::XHugePages::setBytesUsed(XNumber bytesUsed)
{
    return imp_->setBytesUsed(bytesUsed);
}

void vagt::encode::XHugePages::setHugePagesIdentifier(const XString & hugePagesIdentifier)
{
    return imp_->setHugePagesIdentifier(hugePagesIdentifier);
}

void vagt::encode::XHugePages::setVmPageNumberFree(XNumber vmPageNumberFree)
{
    return imp_->setVmPageNumberFree(vmPageNumberFree);
}

void vagt::encode::XHugePages::setBytesFree(XNumber bytesFree)
{
    return imp_->setBytesFree(bytesFree);
}

void vagt::encode::XHugePages::setPercentFree(XNumber percentFree)
{
    return imp_->setPercentFree(percentFree);
}

void vagt::encode::XHugePages::setPercentUsed(XNumber percentUsed)
{
    return imp_->setPercentUsed(percentUsed);
}

void vagt::encode::XHugePages::setVmPageNumberUsed(XNumber vmPageNumberUsed)
{
    return imp_->setVmPageNumberUsed(vmPageNumberUsed);
}
