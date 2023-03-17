#include "StaticResouceController.h"
#include "MediaType.h"

#include <filesystem>
#include <fstream>
#include <iostream> //TODO remove
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
        //TODO verify that the client doesn't have access to filesystem outside of allowed directories
        //TODO is target always a relative URL? Do we need to ignore a query string?
        auto target = request.target();
        std::string targetStr(target.data(), target.size());
        std::string filepath = config->getStaticResouceRootDir() + targetStr;
        std::cout << "Filepath: " << filepath << std::endl;

        std::string responseBody;
        std::string mediaType;
        if (readResourceFromFile(filepath, responseBody)) {
            std::cout << "FOUND: " << filepath << responseBody << std::endl;
            auto fileExtension = fs::path(filepath).extension().string(); //TODO maybe it is better to use path instead of string
            mediaType = mediaTypeResolver->getMediaTypeByExtension(fileExtension);
        } else {
            std::cout << "NOT FOUND: " << filepath << std::endl;
            //TODO maybe it is better to throw error?
            response.result(http::status::not_found);
            if (readResourceFromFile(config->getNotFoundPage(), responseBody)) {
                auto fileExtension = fs::path(config->getNotFoundPage()).extension().string(); //TODO maybe it is better to use path instead of string
                mediaType = mediaTypeResolver->getMediaTypeByExtension(fileExtension);
            } else {
                responseBody = RESOURCE_NOT_FOUND;
                mediaType = TEXT_PLAIN;
            }
        }
        response.body() = std::move(responseBody);
        response.set(http::field::content_type, mediaType);
    }

    bool StaticResouceController::readResourceFromFile(const std::string& filepath, std::string& out) const {
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
