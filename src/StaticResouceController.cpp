#include "StaticResouceController.h"
#include "MediaType.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>

namespace WebServer {

    namespace {
        namespace http = boost::beast::http;
        namespace fs = std::filesystem;

        const char END_OF_STRING = '\0';
        const std::string RESOURCE_NOT_FOUND = "404 Not Found"; //TODO use HTML instead of plain text
    }

    StaticResouceController::StaticResouceController(std::shared_ptr<ApplicationConfig>& config_,
                                                     std::unique_ptr<MediaTypeResolver>& mediaTypeResolver_) 
                                                     : config(config_),
                                                       mediaTypeResolver(std::move(mediaTypeResolver_)) {
    }

    void StaticResouceController::serve(const http::request<http::string_body>& request, http::response<http::string_body>& response) {
        std::string filepath = config->getContentRootDir();
        filepath += request.target(); //TODO verify that the client doesn't have access to filesystem outside of allowed directories

        auto fileExtension = fs::path(filepath).extension();
        if (std::filesystem::is_regular_file(filepath)) {
            if (std::ifstream input{filepath, std::ios::binary | std::ios::ate}) {
                auto fileSize = input.tellg();
                std::string body(fileSize, END_OF_STRING);
                input.seekg(0);
                if (input.read(&body[0], fileSize)) {
                    response.body() = std::move(body);
                    response.set(http::field::content_type, mediaTypeResolver->getMediaTypeByExtension(fileExtension.string()));
                }
            } else {
                //TODO handle error
            }
        } else {
            response.result(http::status::not_found);
            if (std::ifstream input{config->getContentRootDir() + config->getNotFoundPage(), std::ios::binary | std::ios::ate}) {
                auto fileSize = input.tellg();
                std::string body(fileSize, END_OF_STRING);
                input.seekg(0);
                if (input.read(&body[0], fileSize)) {
                    response.body() = std::move(body);
                    response.set(http::field::content_type, mediaTypeResolver->getMediaTypeByExtension(HTML_EXTENSION));
                } else {
                    //TODO handle error
                }
            } else {
                response.body() = RESOURCE_NOT_FOUND;
                response.set(http::field::content_type, TEXT_PLAIN);
            }
        }
    }

}
