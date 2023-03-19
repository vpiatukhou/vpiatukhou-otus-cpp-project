#pragma once

#include <string>
#include <memory>
#include <unordered_map>

namespace WebServer {

    //TODO is it ok to store the constants here?
    const std::string CSS_EXTENSION = ".css";
    const std::string HTML_EXTENSION = ".html";
    const std::string JS_EXTENSION = ".js";

    class MediaTypeResolver {
    public:
        MediaTypeResolver();

        std::string getMediaTypeByExtension(const std::string& fileExtension);

    private:
        std::unordered_map<std::string, std::string> mediaTypeByExtension;

    };

    using MediaTypeResolverPtr = std::shared_ptr<MediaTypeResolver>;

}
