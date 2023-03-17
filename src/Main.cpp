#include "Application.h"

#include <iostream>

int main(int argc, char* argv[]) {
    using namespace WebServer;
    using boost::asio::ip::tcp;

    Port port = 8080;

    try {
        Application application;
        application.start();
    } catch (const std::exception& e) {
        std::cerr << "Internal error: " << e.what() << std::endl;
        return -1; //TODO move to constant
    }

    return 0;
}
