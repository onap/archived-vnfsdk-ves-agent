#include "XJsonObject.h"
#include "XJsonObjectImp.h"

vagt::encode::XJsonObject::XJsonObject()
{
}

vagt::encode::XJsonObject::XJsonObject(const XString & objectName, const XArrayOfXJsonObjectInstance & objectInstances):
    imp_(make_shared<XJsonObjectImp>(objectName, objectInstances))
{
}

void vagt::encode::XJsonObject::setObjectSchema(const XString & objectSchema)
{
    return imp_->setObjectSchema(objectSchema);
}

void vagt::encode::XJsonObject::setObjectName(const XString & objectName)
{
    return imp_->setObjectName(objectName);
}

void vagt::encode::XJsonObject::setNfSubscriptionId(const XString & nfSubscriptionId)
{
    return imp_->setNfSubscriptionId(nfSubscriptionId);
}

void vagt::encode::XJsonObject::setObjectInstances(const XArrayOfXJsonObjectInstance & objectInstances)
{
    return imp_->setObjectInstances(objectInstances);
}

void vagt::encode::XJsonObject::setNfSubscribedObjectName(const XString & nfSubscribedObjectName)
{
    return imp_->setNfSubscribedObjectName(nfSubscribedObjectName);
}

void vagt::encode::XJsonObject::setObjectSchemaUrl(const XString & objectSchemaUrl)
{
    return imp_->setObjectSchemaUrl(objectSchemaUrl);
}
