#pragma once

#include "StaticResouceController.h"

#include <boost/beast/http.hpp>

#include <memory>

namespace WebServer {
    
    class RequestDispatcher {
    public:
        RequestDispatcher(std::shared_ptr<StaticResouceController>& staticResouceController_);

        void dispatch(const boost::beast::http::request<boost::beast::http::string_body>& request,
                      boost::beast::http::response<boost::beast::http::string_body>& response);

    private:
        std::shared_ptr<StaticResouceController> staticResouceController;

    };
}
