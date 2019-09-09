#pragma once

#include <string>
#include <memory>

namespace vagt
{
    namespace queue
    {
        /*************************************************************************************************//**
        * @brief Error codes
        *****************************************************************************************************/
        enum XErrorCode : unsigned short
        {
            XErrorOk,       /**< The operation is successful */
            XErrorNok,      /**< General failure */
            XErrorFull,     /**< The buffer is full */
            XErrorEmpty,    /**< The buffer is empty */
        };

        class XQueue
        {
        public:
            virtual bool empty() = 0;
            virtual XErrorCode push(const std::string& val) = 0;
            virtual void pop() = 0;
            virtual std::string front() = 0;

            /*************************************************************************************************//**
            *    Create a queue in memory with specified capacity.
            *****************************************************************************************************/
            static std::shared_ptr<XQueue> create(int capacity);

            /*************************************************************************************************//**
            *    Create a queue on disk.
            *****************************************************************************************************/
            static std::shared_ptr<XQueue> create(const std::string& path);
        };
    }
}