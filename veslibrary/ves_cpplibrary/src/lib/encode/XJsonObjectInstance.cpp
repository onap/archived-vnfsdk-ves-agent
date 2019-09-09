#include "XJsonObjectInstance.h"
#include "XJsonObjectInstanceImp.h"

vagt::encode::XJsonObjectInstance::XJsonObjectInstance():
    imp_(make_shared<XJsonObjectInstanceImp>())
{
}

vagt::encode::XJsonObjectInstance::XJsonObjectInstance(void*) 
{
}

void vagt::encode::XJsonObjectInstance::setJsonObject(const XJsonObject& jsonObject)
{
    return imp_->setJsonObject(jsonObject);
}

void vagt::encode::XJsonObjectInstance::setObjectInstance(const XString & objectInstance)
{
    return imp_->setObjectInstance(objectInstance);
}

void vagt::encode::XJsonObjectInstance::setObjectInstanceEpochMicrosec(XNumber objectInstanceEpochMicrosec)
{
    return imp_->setObjectInstanceEpochMicrosec(objectInstanceEpochMicrosec);
}

void vagt::encode::XJsonObjectInstance::setObjectKeys(const XArrayOfXKey & objectKeys)
{
    return imp_->setObjectKeys(objectKeys);
}
