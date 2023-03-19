#pragma once

#include "StaticResouceController.h"

#include <boost/beast/http.hpp>

#include <memory>

namespace WebServer {
    
    class RequestDispatcher {
    public:
        RequestDispatcher(StaticResouceControllerPtr staticResouceController_);

        void dispatch(const boost::beast::http::request<boost::beast::http::string_body>& request,
                      boost::beast::http::response<boost::beast::http::string_body>& response);

    private:
        StaticResouceControllerPtr staticResouceController;

    };

    using RequestDispatcherPtr = std::shared_ptr<RequestDispatcher>;
}
