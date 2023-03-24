#pragma once

#include "StaticResouceController.h"

#include <memory>

namespace WebServer {

    /**
     * Dispatches the given request to the appropriate controller, based on HTTP 'target'.
     *
     * This is an entry point for all incoming HTTP requests.
     */
    class RequestDispatcher {
    public:
        RequestDispatcher(StaticResouceControllerPtr staticResouceController_);

        void dispatch(const HttpRequest& request, HttpResponse& response);

    private:
        StaticResouceControllerPtr staticResouceController;

    };

    using RequestDispatcherPtr = std::shared_ptr<RequestDispatcher>;
}
