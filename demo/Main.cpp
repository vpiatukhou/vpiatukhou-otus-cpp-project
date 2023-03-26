#include "Application.h"
#include "BarController.h"
#include "FooController.h"
#include "HttpController.h"

#include <boost/log/trivial.hpp>

#include <vector>
#include <utility>

namespace WebServer {

    const int INTERNAL_ERROR = -1;
}

int main(int argc, char* argv[]) {
    using namespace WebServer;

    std::vector<HttpControllerMapping> controllerMapping;
    controllerMapping.push_back({"/bar", std::make_unique<BarController>()});
    controllerMapping.push_back({"/foo", std::make_unique<FooController>()});

    try {
        Application application;
        application.start(argc, argv, controllerMapping);
    } catch (const std::exception& e) {
        BOOST_LOG_TRIVIAL(fatal) << "An internal error occurred. The application wasn't start: " << e.what();
        return INTERNAL_ERROR;
    }

    return 0;
}
