#include "RequestDispatcher.h"

namespace WebServer {

    namespace {
        namespace http = boost::beast::http;
    }

    //TODO should we use && instead of &?
    RequestDispatcher::RequestDispatcher(std::unique_ptr<StaticResouceController>& staticResouceController_)
        : staticResouceController(std::move(staticResouceController_)) {
    }

    void RequestDispatcher::dispatch(const http::request<http::string_body>& request, http::response<http::string_body>& response) {
        staticResouceController->processRequest(request, response);
    }

}
