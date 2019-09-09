#pragma once

#include <atomic>
#include <chrono>
#include <mutex>
#include <string>
#include <curl/curl.h>
#include "XTransport.h"

namespace vagt 
{
    namespace transport 
    {
        class XLibcurlTransport: public XTransport
        {
        public:
            XLibcurlTransport(const XTransportOption& option);

            virtual ~XLibcurlTransport() {}

            virtual XErrorCode start() override;

            virtual XErrorCode stop() override;

            virtual XErrorCode post(const std::string& event) override;

        private:
            XErrorCode initLibcurl();
            XErrorCode cleanupLibcurl();
            XErrorCode curlPost(const std::string& body);

            static char curlErrorBuf_[CURL_ERROR_SIZE];
            static size_t readCallback(void *ptr, size_t size, size_t nmemb, void *userp);
            static size_t writeCallback(void *ptr, size_t size, size_t nmemb, void *userp);

            XTransportOption option_;
            CURL* curl_;
            struct curl_slist* hdr_;
        };
    }
}
