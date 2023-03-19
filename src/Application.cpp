#include "Application.h"
#include "ApplicationConfig.h"
#include "ProgramOptions.h"
#include "RequestDispatcher.h"
#include "MediaTypeResolver.h"
#include "HttpServer.h"
#include "HttpsServer.h"

#include <iostream>
#include <memory>

namespace WebServer {

    class Application::Impl {
    public:
        void start(int argc, char* argv[]) {
            ProgramOptions options;
            if (options.parse(argc, argv, std::cout)) {
                boost::asio::io_context ioContext;

                std::shared_ptr<MediaTypeResolver> mediaTypeResolver = std::make_shared<MediaTypeResolver>();
                std::shared_ptr<ApplicationConfig> config = std::make_shared<ApplicationConfig>(options.getConfigFilepath());
                std::shared_ptr<StaticResouceController> staticResouceController = std::make_shared<StaticResouceController>(config, mediaTypeResolver);
                std::shared_ptr<RequestDispatcher> requestDispatcher = std::make_shared<RequestDispatcher>(staticResouceController);

                auto port = config->getServerPort();

                std::cout << "The server is listening on the port " << port << '.' << std::endl;

                if (config->isSslEnabled()) {
                    HttpsServer server(ioContext, port, config, requestDispatcher);
                    ioContext.run();
                } else {
                    HttpServer server(ioContext, port, config, requestDispatcher);
                    ioContext.run();
                }
            }
        }

    };

    Application::Application() : impl(std::make_unique<Impl>()) {
    }

    Application::~Application() {
    }

    void Application::start(int argc, char* argv[]) {
        impl->start(argc, argv);
    }

}
