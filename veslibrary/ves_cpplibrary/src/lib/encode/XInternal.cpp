#include "XInternal.h"

json vagt::encode::mergeCommonValues(json jsonObj, const std::map<std::string, XCommonValue>& values)
{
    for (auto it : values)
    {
        if (XDataTypeInteger == it.second.dataType_)
        {
            jsonObj[it.first] = it.second.intVal_;
        }
        else if (XDataTypeNumber == it.second.dataType_)
        {
            jsonObj[it.first] = it.second.numberVal_;
        }
        else if (XDataTypeString == it.second.dataType_)
        {
            jsonObj[it.first] = it.second.strVal_;
        }
    }

    return jsonObj;
}
