#pragma once

#include "ApplicationConfig.h"
#include "MediaTypeResolver.h"

#include <boost/beast/http.hpp>

#include <string>
#include <unordered_map>
#include <memory>

namespace WebServer {
    
    class StaticResouceController {
    public:
        StaticResouceController(std::shared_ptr<ApplicationConfig>& config_, std::unique_ptr<MediaTypeResolver>& mediaTypeResolver_);

        void processRequest(const boost::beast::http::request<boost::beast::http::string_body>& request,
                   boost::beast::http::response<boost::beast::http::string_body>& response);

    private:
        std::unordered_map<std::string, std::string> mediaTypeByExtension; //TODO move to separate class. Allow the user to add its own mapping.
        std::shared_ptr<ApplicationConfig> config;
        std::unique_ptr<MediaTypeResolver> mediaTypeResolver;

        bool readResourceFromFile(const std::string& filepath, std::string& out) const;

    };
}
