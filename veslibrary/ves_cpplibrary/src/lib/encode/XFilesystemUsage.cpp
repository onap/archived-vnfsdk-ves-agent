#include "XFilesystemUsage.h"
#include "XFilesystemUsageImp.h"

vagt::encode::XFilesystemUsage::XFilesystemUsage()
{
}

vagt::encode::XFilesystemUsage::XFilesystemUsage(const XString & filesystemName, XNumber blockConfigured, XNumber blockIops, XNumber blockUsed, XNumber ephemeralConfigured, XNumber ephemeralIops, XNumber ephemeralUsed):
    imp_(make_shared<XFilesystemUsageImp>(filesystemName, blockConfigured, blockIops, blockUsed, ephemeralConfigured, ephemeralIops, ephemeralUsed ))
{
}

void vagt::encode::XFilesystemUsage::setBlockConfigured(XNumber blockConfigured)
{
    return imp_->setBlockConfigured(blockConfigured);
}

void vagt::encode::XFilesystemUsage::setBlockUsed(XNumber blockUsed)
{
    return imp_->setBlockUsed(blockUsed);
}

void vagt::encode::XFilesystemUsage::setEphemeralConfigured(XNumber ephemeralConfigured)
{
    return imp_->setEphemeralConfigured(ephemeralConfigured);
}

void vagt::encode::XFilesystemUsage::setEphemeralIops(XNumber ephemeralIops)
{
    return imp_->setEphemeralIops(ephemeralIops);
}

void vagt::encode::XFilesystemUsage::setFilesystemName(const XString & filesystemName)
{
    return imp_->setFilesystemName(filesystemName);
}

void vagt::encode::XFilesystemUsage::setBlockIops(XNumber blockIops)
{
    return imp_->setBlockIops(blockIops);
}

void vagt::encode::XFilesystemUsage::setEphemeralUsed(XNumber ephemeralUsed)
{
    return imp_->setEphemeralUsed(ephemeralUsed);
}
