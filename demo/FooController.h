#pragma once

#include "HttpController.h"

namespace WebServer {

    class FooController : public HttpController {

        void processRequest(HttpRequestHolder& requestHolder, HttpResponse& response) override;

    };

}
