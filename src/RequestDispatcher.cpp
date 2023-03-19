#include "RequestDispatcher.h"

namespace WebServer {

    namespace {
        namespace http = boost::beast::http;
    }

    RequestDispatcher::RequestDispatcher(StaticResouceControllerPtr staticResouceController_)
        : staticResouceController(staticResouceController_) {
    }

    void RequestDispatcher::dispatch(const http::request<http::string_body>& request, http::response<http::string_body>& response) {
        staticResouceController->processRequest(request, response);
    }

}
