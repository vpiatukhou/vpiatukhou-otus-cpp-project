#include "StaticResouceController.h"
#include "MediaType.h"
#include "UrlUtil.h"

#include <filesystem>
#include <fstream>
#include <iostream> //TODO remove
#include <utility>

namespace WebServer {

    namespace {
        namespace fs = std::filesystem;
        namespace http = boost::beast::http;

        const std::string METHOD_NOT_ALLOWED = "404 Method Not Allowed";
        const std::string RESOURCE_NOT_FOUND = "404 Not Found";
        const std::string FORBIDDEN = "403 Forbidden";
        const char END_OF_STRING = '\0';
        const char QUERY_BEGIN_MARK = '?';
    }

    StaticResouceController::StaticResouceController(ApplicationConfigPtr config_,
                                                     MediaTypeResolverPtr mediaTypeResolver_)
        : config(config_), mediaTypeResolver(std::move(mediaTypeResolver_)) {
    }

    void StaticResouceController::processRequest(const HttpRequest& request,  HttpResponse& response) {
        if (request.method() != http::verb::get) {
            response.result(http::status::method_not_allowed);
            response.set(http::field::content_type, MEDIA_TYPE_TEXT_PLAIN);
            response.body() = METHOD_NOT_ALLOWED;
            return;
        }

        auto target = request.target();
        auto requestUri = removeQueryString(std::string(target.data(), target.size()));
        
        fs::path filepath = config->getStaticResouceRootDir();
        filepath += requestUri;
        filepath = filepath.lexically_normal();

        std::cout << "Requested resource: " << filepath.string() << std::endl;//TODO remove

        if (!checkIfPathStartsWithRoot(filepath, config->getStaticResouceRootDir())) {
            response.result(http::status::forbidden);
            response.set(http::field::content_type, MEDIA_TYPE_TEXT_PLAIN);
            response.body() = FORBIDDEN;
            return;
        }

        std::string responseBody;
        std::string mediaType;
        if (readResourceFromFile(filepath, responseBody)) {
            mediaType = mediaTypeResolver->getMediaTypeByTarget(filepath.string()); //TODO
        } else {
            std::cout << "Resource " << filepath << " was not found." << std::endl;//TODO remove

            //TODO maybe it is better to throw error?
            response.result(http::status::not_found);
            if (readResourceFromFile(config->getNotFoundPage(), responseBody)) {
                mediaType = mediaTypeResolver->getMediaTypeByTarget(config->getNotFoundPage().string()); //TODO
            } else {
                responseBody = RESOURCE_NOT_FOUND;
                mediaType = MEDIA_TYPE_TEXT_PLAIN;
            }
        }
        response.set(http::field::content_type, mediaType);
        response.body() = std::move(responseBody);
    }

    bool StaticResouceController::readResourceFromFile(const fs::path& filepath, std::string& out) const {
        if (std::filesystem::is_regular_file(filepath)) {
            if (std::ifstream input{filepath, std::ios::binary | std::ios::ate}) {
                auto fileSize = input.tellg();
                out.resize(fileSize, END_OF_STRING); //TODO optimize it
                input.seekg(0);
                if (input.read(out.data(), fileSize)) {
                    return true;
                }
            }
        }
        return false;
    }

}
