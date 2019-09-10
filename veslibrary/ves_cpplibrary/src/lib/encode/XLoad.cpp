#include "XLoad.h"
#include "XLoadImp.h"

vagt::encode::XLoad::XLoad():
    imp_(make_shared<XLoadImp>())
{
}

vagt::encode::XLoad::XLoad(void*)
{

}

void vagt::encode::XLoad::setShortTerm(XNumber shortTerm)
{
    return imp_->setShortTerm(shortTerm);
}

void vagt::encode::XLoad::setLongTerm(XNumber longTerm)
{
    return imp_->setLongTerm(longTerm);
}

void vagt::encode::XLoad::setMidTerm(XNumber midTerm)
{
    return imp_->setMidTerm(midTerm);
}
