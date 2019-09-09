#pragma once
        
#include "XBatch.h"
#include "XInternal.h"

namespace vagt
{
    namespace encode
    {
        class XBatchImp: public XBatch, public XJsonable
        {
        public:
            virtual std::string toString() override;

            virtual json toJson() override;

            virtual void addEvent(std::shared_ptr<vagt::encode::XSerialable> event) override;

        private:
            std::vector<std::shared_ptr<vagt::encode::XSerialable>> events_;
        };
    }
}
        