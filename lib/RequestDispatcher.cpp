#include "RequestDispatcher.h"

#include "UrlUtil.h"

#include <utility>

namespace WebServer {

    RequestDispatcher::RequestDispatcher(StaticResouceControllerPtr staticResouceController_,
        std::vector<HttpControllerMapping>&& controllerMapping_)
        : staticResouceController(staticResouceController_), controllerMapping(std::move(controllerMapping_)) {
    }

    void RequestDispatcher::dispatch(HttpRequestHolder& request, HttpResponse& response) {
        auto requestUri = request.getRequestUri();
        for (auto& mapping : controllerMapping) {
            if (mapping.requestUri == requestUri) {
                mapping.controller->processRequest(request, response);
                return;
            }
        }
        staticResouceController->processRequest(request, response);
    }

}
