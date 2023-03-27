#pragma once

#include "HttpController.h"
#include "StaticResouceController.h"

#include <memory>
#include <vector>

namespace WebServer {

    /**
     * Dispatches the given request to the appropriate controller, based on HTTP 'target'.
     *
     * This is an entry point for all incoming HTTP requests.
     */
    class RequestDispatcher {
    public:
        RequestDispatcher(StaticResouceControllerPtr staticResouceController_, std::vector<HttpControllerMapping>&& controllerMapping_);

        void dispatch(HttpRequestHolder& requestHolder, HttpResponse& response);

    private:
        StaticResouceControllerPtr staticResouceController;

        std::vector<HttpControllerMapping> controllerMapping;

    };

    using RequestDispatcherPtr = std::shared_ptr<RequestDispatcher>;
}
