#include "Application.h"
#include "ApplicationConfig.h"
#include "RequestDispatcher.h"
#include "MediaTypeResolver.h"
//#include "Server.h"
#include "SslServer.h"

#include <iostream>
#include <memory>

namespace WebServer {

    class Application::Impl {
    public:
        void start() {
            using boost::asio::ip::tcp;

            boost::asio::io_context ioContext;

            //TODO does it make sense to use shared_ptr for all types?
            std::unique_ptr<MediaTypeResolver> mediaTypeResolver = std::make_unique<MediaTypeResolver>();
            std::shared_ptr<ApplicationConfig> config = std::make_shared<ApplicationConfig>("/app/resources/application.json"); //TODO read from command line arguments
            std::unique_ptr<StaticResouceController> staticResouceController = std::make_unique<StaticResouceController>(config, mediaTypeResolver);
            std::shared_ptr<RequestDispatcher> requestDispatcher = std::make_shared<RequestDispatcher>(staticResouceController);

            auto port = config->getServerPort();
            SslServer server(ioContext, port, config, requestDispatcher);

            std::cout << "The server is listening on the port " << port << '.' << std::endl;

            ioContext.run();
        }

    };

    Application::Application() : impl(std::make_unique<Impl>()) {
    }

    Application::~Application() {
    }

    void Application::start() {
        impl->start();
    }

}
