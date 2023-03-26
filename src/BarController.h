#pragma once

#include "HttpController.h"

namespace WebServer {

    class BarController : public HttpController {

        void processRequest(HttpRequestHolder& requestHolder, HttpResponse& response) override;

    };

}
