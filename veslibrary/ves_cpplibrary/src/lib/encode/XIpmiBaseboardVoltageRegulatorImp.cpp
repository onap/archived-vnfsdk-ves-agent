#include "XIpmiBaseboardVoltageRegulatorImp.h"

XIpmiBaseboardVoltageRegulatorImp::XIpmiBaseboardVoltageRegulatorImp(const XString& baseboardVoltageRegulatorIdentifier):
        baseboardVoltageRegulatorIdentifier_(baseboardVoltageRegulatorIdentifier)
{

}

void XIpmiBaseboardVoltageRegulatorImp::setBaseboardVoltageRegulatorIdentifier(const XString& baseboardVoltageRegulatorIdentifier)
{
    comVals_["baseboardVoltageRegulatorIdentifier"] = baseboardVoltageRegulatorIdentifier;
}
            
void XIpmiBaseboardVoltageRegulatorImp::setVoltageRegulatorTemperature(XNumber voltageRegulatorTemperature)
{
    comVals_["voltageRegulatorTemperature"] = voltageRegulatorTemperature;
}

json XIpmiBaseboardVoltageRegulatorImp::toJson()
{
    try
    {
        json field = {
            {"baseboardVoltageRegulatorIdentifier", baseboardVoltageRegulatorIdentifier_}
        };

        //optional val
        
        field = mergeCommonValues(field, comVals_);

        return field;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XIpmiBaseboardVoltageRegulator to json object:{}.", e.what());
        return json();
    }
}
            