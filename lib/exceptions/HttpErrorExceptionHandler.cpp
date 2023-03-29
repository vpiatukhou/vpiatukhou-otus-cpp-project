#include "HttpErrorExceptionHandler.h"

#include <boost/beast/http.hpp>
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
        bool readResourceFromFile(const fs::path& filepath, std::string& out) {
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

        bool tryToGetErrorPagePath(const ApplicationConfigPtr& config, boost::beast::http::status status, fs::path& pageFilepath) {
            try {
                //TODO replace unsigned int with alias
                pageFilepath = config->getErrorPageMapping().at(static_cast<unsigned int>(status));
            } catch (std::out_of_range& e) {
                return false;
            }
            return true;
        }
    }

    void HttpErrorExceptionHandler::handle(const HttpErrorException& exception, HttpResponse& response) {
        auto httpStatus = exception.getHttpStatus();

        fs::path pageFilepath;
        if (tryToGetErrorPagePath(config, httpStatus, pageFilepath)) {
            auto mediaType = mediaTypeResolver->getMediaTypeByFilename(pageFilepath.filename().string());
            std::string responseBody;
            readResourceFromFile(pageFilepath, responseBody);
            response.set(http::field::content_type, std::move(mediaType));
            response.result(httpStatus);
            response.body() = std::move(responseBody);
        } else {
            BOOST_LOG_TRIVIAL(warning) << "There is no an error page for HTTP status '" << httpStatus << "'.";
            response.result(httpStatus);
            response.body() = "";
        }
    }

}
