#pragma once

#include "ApplicationConfig.h"

#include <memory>
#include <regex>
#include <string>
#include <vector>
#include <utility>

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
        std::vector<std::pair<std::regex, std::string>> mediaTypesMapping;
    };

    using MediaTypeResolverPtr = std::shared_ptr<MediaTypeResolver>;

}
