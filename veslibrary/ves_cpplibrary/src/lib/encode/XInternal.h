#pragma once

#include "XEvent.h"
#include "nlohmann/json.hpp"

#ifndef SPDLOG_ACTIVE_LEVEL 
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif

#include "spdlog/spdlog.h"

using namespace std;
using namespace vagt::encode;
using json = nlohmann::json;

namespace vagt
{
    namespace encode
    {
        class XJsonable
        {
        public:
            virtual json toJson() = 0;
        };

        class XCommonValue
        {
        public:
            XCommonValue() :dataType_(XDataTypeUnknown) {}
            XCommonValue(const std::string& val) :dataType_(XDataTypeString), strVal_(val) {}
            XCommonValue(XInteger val) :dataType_(XDataTypeInteger), intVal_(val) {}
            XCommonValue(XNumber val) :dataType_(XDataTypeNumber), numberVal_(val) {}

            XDataType dataType_;
            XInteger intVal_;
            XNumber numberVal_;
            XString strVal_;
        };

        json mergeCommonValues(json jsonObj, const std::map<std::string, XCommonValue>& values);

        template <class T>
        inline json fromArray(const T& v)
        {
            json jsonArray = json::array();
            for (auto e : v)
            {
                jsonArray.push_back(dynamic_pointer_cast<XJsonable>(e.imp_)->toJson());
            }
            return jsonArray;
        }
    }
}
