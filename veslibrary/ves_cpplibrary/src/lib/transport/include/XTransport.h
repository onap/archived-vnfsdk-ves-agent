#pragma once
/*************************************************************************************************//**
@file     XTransport.h
@brief    Transport API, used to send string to collector
*****************************************************************************************************/
#include <memory>
#include <atomic>
#include <string>
#include <vector>
#include <chrono>
#include "XQueue.h"

namespace vagt 
{
    namespace transport
    {
        /*************************************************************************************************//**
        * @brief Error codes
        *****************************************************************************************************/
        enum XErrorCode: unsigned short
        {
            XErrorOk,                /**< The operation is successful  */
            XErrorNok,               /**< General failure */  
            XErrorTimeout,           /**< Timeout */  
            XErrorUnauthorized,      /**< Unauthorized */
            XErrorCanceled,          /**< The operation is canceled */
            XErrorClientError,       /**< Client error, e.g. HTTP 404 */  
            XErrorServerError,       /**< Server error, e.g. HTTP 500 */  
            XErrorNetworkError,      /**< Network error */  
        };

        /*************************************************************************************************//**
        * @brief Transport option
        *****************************************************************************************************/
        class XTransportOption
        {
        public:
            std::string host_;                          /**< Remote RPC server hostname or IP address*/
            int port_;                                  /**< Remote RPC server port */
            std::chrono::milliseconds timeOut_;         /**< Timeout */
            std::string url_;                           /**< URL of Collector */
            std::string sourceIp_;                      /**< Source IP Address */
            bool secure_;                               /**< Enable TLS or not */
            std::string caInfo_;                        /**< CA INFO for TLS */
            std::string caFilePath_;                    /**< CA pATH for TLS */
            std::string certFilePath_;                  /**< CERT for TLS */
            std::string keyFilePath_;                   /**< KEY for TLS */
            long verifyPeer_;                           /**< Refer to CURLOPT_SSL_VERIFYPEER */
            long verifyHost_;                           /**< Refer to CURLOPT_SSL_VERIFYHOST */
            std::string userName_;                      /**< User name */
            std::string userPasswd_;                    /**< Password */

            XTransportOption():secure_(false),verifyPeer_(1),verifyHost_(2)
            {}
        };

        /*************************************************************************************************//**
        * @brief Transport interface
        *****************************************************************************************************/
        class XTransport
        {
        public:
            XTransport();

            /*************************************************************************************************//**
            *    Start Transport and the decorated transports.
            *
            *    @note           This method will call allowPost().
            *****************************************************************************************************/
            virtual XErrorCode start() = 0;

            /*************************************************************************************************//**
            *    Stop Transport and the decorated transports.
            *
            *    @note           This method will call cancelPost().
            *****************************************************************************************************/
            virtual XErrorCode stop() = 0;

            /*************************************************************************************************//**
            *    Post event string.
            *****************************************************************************************************/
            virtual XErrorCode post(const std::string& event) = 0;

            /*************************************************************************************************//**
            *    Cancel the running and subsequent post() until allowPost() is called.
            *    It is useful especially when transport is wrapped by SynchronizedTransport.
            *****************************************************************************************************/
            virtual void cancelPost();

            /*************************************************************************************************//**
            *    Allow the post() method. 
            *****************************************************************************************************/
            virtual void allowPost();

            /*************************************************************************************************//**
            *    Check if the post() method will be canceled. 
            *****************************************************************************************************/
            virtual bool shouldCancelPost();
 
            /*************************************************************************************************//**
            *    Create a libcurl based transport.
            *****************************************************************************************************/
            static std::shared_ptr<XTransport> LibCurlTransport(const XTransportOption& option);

            /*************************************************************************************************//**
            *    Create a retry transport decorator. 
            *    The retry will be performed if the decorated post() does NOT return 
            *    XErrorOk, XErrorCanceled or XErrorClientError.
            *****************************************************************************************************/
            static std::shared_ptr<XTransport> RetryTransport(std::shared_ptr<XTransport> transport,
                std::chrono::milliseconds retryInterval, 
                int retryTimes);

            /*************************************************************************************************//**
            *    Create a switchable transport decorator.
            *    The transport will be switched if the decorated post() does NOT return 
            *    XErrorOk, XErrorCanceled or XErrorClientError.
            *****************************************************************************************************/
            static std::shared_ptr<XTransport> SwitchableTransport(std::vector<std::shared_ptr<XTransport>>& transports);

            /*************************************************************************************************//**
            *    Create a synchronized transport decorator. 
            *    The decorated transport will be thread safe.
            *****************************************************************************************************/
            static std::shared_ptr<XTransport> SynchronizedTransport(std::shared_ptr<XTransport> transport);

            /*************************************************************************************************//**
            *    Create a bufferd(FIFO) transport decorator. 
            *    The event string will be buffered first and then post via decorated transport.
            *****************************************************************************************************/
            static std::shared_ptr<XTransport> BufferedTransport(std::shared_ptr<XTransport> transport, std::shared_ptr<vagt::queue::XQueue> queue);

            /*************************************************************************************************//**
            *    Create a RPC client transport. 
            *****************************************************************************************************/
            static std::shared_ptr<XTransport> RpcClientTransport(const XTransportOption& option);

            /*************************************************************************************************//**
            *    Create a RPC server transport. 
            *****************************************************************************************************/
            static std::shared_ptr<XTransport> RpcServerTransport(std::shared_ptr<XTransport> transport, const XTransportOption& option);

        protected:
           std::atomic<bool> cancel_;

        private:
            XTransport(const XTransport&) = delete;
            XTransport& operator=(const XTransport&) = delete;
        };
    }
}
