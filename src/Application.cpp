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

                //TODO does it make sense to use shared_ptr for all types?
                std::unique_ptr<MediaTypeResolver> mediaTypeResolver = std::make_unique<MediaTypeResolver>();
                std::shared_ptr<ApplicationConfig> config = std::make_shared<ApplicationConfig>(options.getConfigFilepath());
                std::unique_ptr<StaticResouceController> staticResouceController = std::make_unique<StaticResouceController>(config, mediaTypeResolver);
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
