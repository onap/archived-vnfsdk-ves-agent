#include "XBatchImp.h"

std::string XBatchImp::toString()
{
    try
    {
        auto js = toJson();
        return js.dump();
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to dump XIpmiNic to json string:{}.", e.what());
        return "";
    }
}

void XBatchImp::addEvent(shared_ptr<XSerialable> event)
{
    events_.push_back(event);
}

nlohmann::json vagt::encode::XBatchImp::toJson()
{
    try
    {
        json field = json::array();

        for (auto event : events_)
        {
            if (event)
            {
                field.push_back( dynamic_pointer_cast<XJsonable>(event)->toJson()["event"]);
            }
        }

        json jsEvent;
        jsEvent["eventList"] = field;
        return jsEvent;
    }
    catch (json::exception& e)
    {
        SPDLOG_ERROR("Fail to build XBatch to json object:{}.", e.what());
        return json();
    }
}
