#include "RequestDispatcher.h"

namespace WebServer {

    RequestDispatcher::RequestDispatcher(StaticResouceControllerPtr staticResouceController_)
        : staticResouceController(staticResouceController_) {
    }

    void RequestDispatcher::dispatch(const HttpRequest& request, HttpResponse& response) {
        //at the moment only StaticResourceController is supported
        staticResouceController->processRequest(request, response);
    }

}
