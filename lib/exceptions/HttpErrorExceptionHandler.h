#pragma once

#include "HttpErrorException.h"
#include "../ApplicationConfig.h"
#include "../HttpRequestHolder.h"
#include "../MediaTypeResolver.h"

#include <memory>

namespace WebServer {

    class HttpErrorExceptionHandler  {
    public:
        HttpErrorExceptionHandler(ApplicationConfigPtr config_, MediaTypeResolverPtr mediaTypeResolver_) 
            : config(config_), mediaTypeResolver(mediaTypeResolver_) {
        }

        void handle(const HttpErrorException& exception, HttpResponse& response);

    private:
        ApplicationConfigPtr config;
        MediaTypeResolverPtr mediaTypeResolver;
    };

    using HttpErrorExceptionHandlerPtr = std::shared_ptr<HttpErrorExceptionHandler>;

}
