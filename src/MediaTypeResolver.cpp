#include "MediaTypeResolver.h"
#include "MediaType.h"

namespace WebServer {

    MediaTypeResolver::MediaTypeResolver() {
        mediaTypeByExtension[CSS_EXTENSION] = TEXT_CSS;
        mediaTypeByExtension[HTML_EXTENSION] = TEXT_HTML;
        mediaTypeByExtension[JS_EXTENSION] = TEXT_JAVASCRIPT;
    }

    std::string MediaTypeResolver::getMediaTypeByExtension(const std::string& fileExtension) {
        auto it = mediaTypeByExtension.find(fileExtension);
        if (it == mediaTypeByExtension.end()) {
            return APPLICATION_OCTET_STREAM; //TODO is it correct to send this type for unknown content?
        }
        return it->second;
    }

}
