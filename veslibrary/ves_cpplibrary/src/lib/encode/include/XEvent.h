#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace vagt 
{
    namespace encode
    {
        using XInteger = long;
        using XNumber = double;
        using XString = std::string;
        using XHashMap = std::map<std::string, std::string>;
        using XArrayOfString = std::vector<std::string>;

        enum XDataType : unsigned short
        {
            XDataTypeUnknown,
            XDataTypeInteger,
            XDataTypeNumber,
            XDataTypeString,
        };

        class XSerialable
        {
        public:
            virtual std::string toString() = 0;
        };
    }
}
