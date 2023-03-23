#pragma once

#include "ApplicationConfig.h"

#include <memory>
#include <regex>
#include <string>
#include <vector>

namespace WebServer {

    class MediaTypeResolver {
    public:
        MediaTypeResolver(const std::vector<MediaTypeMapping>& mediaTypeMapping);
        MediaTypeResolver(const MediaTypeResolver&) = delete;
        MediaTypeResolver(MediaTypeResolver&&) = delete;
        ~MediaTypeResolver() = default;

        MediaTypeResolver& operator=(const MediaTypeResolver&) = delete;
        MediaTypeResolver& operator=(MediaTypeResolver&&) = delete;

        std::string getMediaTypeByTarget(const std::string& requestTarget);

    private:
        struct MediaTypeByFilename {
            std::regex filenameRegEx;
            std::string mediaType;
        };

        std::vector<MediaTypeByFilename> mediaTypes;
    };

    using MediaTypeResolverPtr = std::shared_ptr<MediaTypeResolver>;

}
