#pragma once

#include "ApplicationConfig.h"
#include "HttpRequestResponse.h"
#include "MediaTypeResolver.h"

#include <boost/beast/http.hpp>

#include <filesystem>

namespace WebServer {

    /**
     * Handles HTTP GET requests and returns static resources like HTML, javascript, images etc.
     */
    class StaticResouceController {
    public:
        StaticResouceController(ApplicationConfigPtr config_, MediaTypeResolverPtr mediaTypeResolver_);

        /**
         * Returns the resource (HTML, JS, CSS etc.) which is specified in 'target' of the given HTTP request.
         * The resource is written to the response.
         * 
         * In case of an error some of the following HTTP codes can be returned:
         * 
         * 401 - if the target URL points to the resource outside of the base directory (please see ApplicationConfig::getStaticResouceBaseDir()).
         * 404 - if the resource doesn't exist.
         * 405 - if the request method is not GET.
         * 
         * @param request   - HTTP request
         * @param response  - HTTP response
         */
        void processRequest(const HttpRequest& request, HttpResponse& response);

    private:
        ApplicationConfigPtr config;
        MediaTypeResolverPtr mediaTypeResolver;

        void processGetRequest(const HttpRequest& request, HttpResponse& response) const;
        void setUpErrorResponse(HttpResponse& response, boost::beast::http::status status, 
                                const std::filesystem::path& errorPage, const std::string& fallbackResponseMsg) const;
    };

    using StaticResouceControllerPtr = std::shared_ptr<StaticResouceController>;
}
