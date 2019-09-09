#include "XIpmiBaseboardVoltageRegulator.h"
#include "XIpmiBaseboardVoltageRegulatorImp.h"

vagt::encode::XIpmiBaseboardVoltageRegulator::XIpmiBaseboardVoltageRegulator()
{
}

vagt::encode::XIpmiBaseboardVoltageRegulator::XIpmiBaseboardVoltageRegulator(const XString & baseboardVoltageRegulatorIdentifier):
    imp_(make_shared<XIpmiBaseboardVoltageRegulatorImp>(baseboardVoltageRegulatorIdentifier))
{
}

void vagt::encode::XIpmiBaseboardVoltageRegulator::setBaseboardVoltageRegulatorIdentifier(const XString & baseboardVoltageRegulatorIdentifier)
{
    return imp_->setBaseboardVoltageRegulatorIdentifier(baseboardVoltageRegulatorIdentifier);
}

void vagt::encode::XIpmiBaseboardVoltageRegulator::setVoltageRegulatorTemperature(XNumber voltageRegulatorTemperature)
{
    return imp_->setVoltageRegulatorTemperature(voltageRegulatorTemperature);
}
