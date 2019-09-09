#include "XNamedHashMap.h"
#include "XNamedHashMapImp.h"

vagt::encode::XNamedHashMap::XNamedHashMap()
{
}

vagt::encode::XNamedHashMap::XNamedHashMap(const XString & name, const XHashMap & hashMap):
    imp_(make_shared<XNamedHashMapImp>(name, hashMap))
{
}

void vagt::encode::XNamedHashMap::setName(const XString & name)
{
    return imp_->setName(name);
}

void vagt::encode::XNamedHashMap::setHashMap(const XHashMap & hashMap)
{
    return imp_->setHashMap(hashMap);
}
