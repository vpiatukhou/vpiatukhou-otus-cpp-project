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
        StaticResouceController(ApplicationConfigPtr config_, MediaTypeResolverPtr mediaTypeResolver_);

        void processRequest(const boost::beast::http::request<boost::beast::http::string_body>& request,
                   boost::beast::http::response<boost::beast::http::string_body>& response);

    private:
        ApplicationConfigPtr config;
        MediaTypeResolverPtr mediaTypeResolver;

        bool readResourceFromFile(const std::string& filepath, std::string& out) const;

    };

    using StaticResouceControllerPtr = std::shared_ptr<StaticResouceController>;
}
