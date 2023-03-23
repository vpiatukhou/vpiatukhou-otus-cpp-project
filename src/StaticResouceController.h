#pragma once

#include "ApplicationConfig.h"
#include "HttpRequestResponse.h"
#include "MediaTypeResolver.h"

#include <boost/beast/http.hpp>

#include <memory>
#include <string>
#include <unordered_map>

namespace WebServer {

    /**
     * Manages static resources like HTML, javascript, images etc.
     */
    class StaticResouceController {
    public:
        StaticResouceController(ApplicationConfigPtr config_, MediaTypeResolverPtr mediaTypeResolver_);

        /**
         * Loads a requested resources (HTML, CSS etc.) and writes it to the response.
         * 
         * @param request   - HTTP request
         * @param response  - HTTP response
         */
        void processRequest(const HttpRequest& request, HttpResponse& response);

    private:
        ApplicationConfigPtr config;
        MediaTypeResolverPtr mediaTypeResolver;

        bool isPathInsideRootDir(const std::filesystem::path& filepath) const;
        bool readResourceFromFile(const std::filesystem::path& filepath, std::string& out) const;

    };

    using StaticResouceControllerPtr = std::shared_ptr<StaticResouceController>;
}
