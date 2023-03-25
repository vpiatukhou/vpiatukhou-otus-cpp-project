#include "Application.h"

#include <boost/log/trivial.hpp>

namespace WebServer {

    const int INTERNAL_ERROR = -1;
}

int main(int argc, char* argv[]) {
    using namespace WebServer;

    try {
        Application application;
        application.start(argc, argv);
    } catch (const std::exception& e) {
        BOOST_LOG_TRIVIAL(fatal) << "An internal error occurred. The application wasn't start: " << e.what();
        return INTERNAL_ERROR;
    }

    return 0;
}
