#include "MediaTypeResolver.h"
#include "MediaType.h"

namespace WebServer {

    namespace {
        const std::regex CSS_PATTERN(".+[.]css$");
        const std::regex HTML_PATTERN(".+[.]html$");
        const std::regex JS_PATTERN(".+[.]js$");
        const std::regex JPEG_PATTERN(".+[.](jpeg|jpg)$");
        const std::regex PNG_PATTERN(".+[.]png$");
        const std::regex SVG_PATTERN(".+[.]svg$");
    }

    MediaTypeResolver::MediaTypeResolver(const std::vector<MediaTypeMapping>& mediaTypeMapping) {
        for (auto& config : mediaTypeMapping) {
            mediaTypes.push_back({ std::regex(config.fileRegExp), config.mediaType });
        }

        mediaTypes.push_back({ CSS_PATTERN, MEDIA_TYPE_TEXT_CSS });
        mediaTypes.push_back({ HTML_PATTERN, MEDIA_TYPE_TEXT_HTML });
        mediaTypes.push_back({ JS_PATTERN, MEDIA_TYPE_TEXT_JAVASCRIPT });
        mediaTypes.push_back({ JPEG_PATTERN, MEDIA_TYPE_IMAGE_JPEG });
        mediaTypes.push_back({ PNG_PATTERN, MEDIA_TYPE_IMAGE_PNG });
        mediaTypes.push_back({ SVG_PATTERN, MEDIA_TYPE_IMAGE_SVG });
    }

    std::string MediaTypeResolver::getMediaTypeByTarget(const std::string& requestTarget) {
        for (auto& mediaType : mediaTypes) {
            std::smatch match;
            if (std::regex_match(requestTarget, match, mediaType.filenameRegEx)) {
                return mediaType.mediaType;
            }
        }
        return MEDIA_TYPE_APPLICATION_OCTET_STREAM;
    }

}
