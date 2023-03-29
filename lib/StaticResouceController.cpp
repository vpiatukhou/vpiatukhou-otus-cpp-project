#include "StaticResouceController.h"
#include "exceptions/HttpErrorException.h"
#include "MediaType.h"
#include "UrlUtil.h"

#include <boost/log/trivial.hpp>

#include <filesystem>
#include <fstream>
#include <utility>

namespace WebServer {

    namespace {
        using namespace std::string_literals;
        namespace fs = std::filesystem;
        namespace http = boost::beast::http;

        const char END_OF_STRING = '\0';

        /**
         * Reads the given file into the given string.
         * 
         * @param filepath  - the file to be read
         * @param out       - the file content is written to this string
         * @return TRUE if the file has been succesfully read.
         *         FALSE - otherwise (e.g. the filepath refers to a directory instead of file).
         */
        bool readResourceFromFile(const fs::path& filepath, std::string& out) { //TODO move to utility
            if (fs::is_regular_file(filepath)) {
                if (std::ifstream input{filepath, std::ios::binary | std::ios::ate}) {
                    auto fileSize = input.tellg();
                    out.resize(fileSize, END_OF_STRING);
                    input.seekg(0);
                    if (input.read(out.data(), fileSize)) {
                        return true;
                    }
                }
            }
            return false;
        }
    }

    StaticResouceController::StaticResouceController(ApplicationConfigPtr config_,
                                                     MediaTypeResolverPtr mediaTypeResolver_)
        : config(config_), mediaTypeResolver(std::move(mediaTypeResolver_)) {
    }

    void StaticResouceController::processRequest(HttpRequestHolder& requestHolder,  HttpResponse& response) {
        if (requestHolder.getRequest().method() == http::verb::get) {
            processGetRequest(requestHolder.getRequestUri(), response);
        } else {
            BOOST_LOG_TRIVIAL(info) << "The method '" << requestHolder.getRequest().method() 
                << "' is not supported in StaticResouceController.";
            throw HttpErrorException(http::status::method_not_allowed);
        }
    }

    void StaticResouceController::processGetRequest(const std::string& requestUri, HttpResponse& response) const {
        auto filepath = config->getStaticResouceBaseDir();
        filepath += requestUri;
        filepath = filepath.lexically_normal();

        BOOST_LOG_TRIVIAL(trace) << "Getting the resource: " << filepath;

        std::string responseBody;
        if (checkIfPathStartsWithBase(filepath, config->getStaticResouceBaseDir())) {
            if (readResourceFromFile(filepath, responseBody)) {
                auto mediaType = mediaTypeResolver->getMediaTypeByFilename(filepath.filename().string());
                response.result(http::status::ok);
                response.set(http::field::content_type, std::move(mediaType));
                response.body() = std::move(responseBody);
            } else {
                BOOST_LOG_TRIVIAL(info) << "The resource " << filepath << " was not found.";
                throw HttpErrorException(http::status::not_found);
            }
        } else {
            BOOST_LOG_TRIVIAL(info) << "Access to " << filepath << " is forbidden.";
            throw HttpErrorException(http::status::forbidden);
        }
    }

}
