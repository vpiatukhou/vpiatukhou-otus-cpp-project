#pragma once

#include "Port.h"
#include "ApplicationConfig.h"
#include "RequestDispatcher.h"

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <memory>

namespace WebServer {

    /**
     * An asynchronous TCP server. Creates a new TcpConnection object for an each incoming connection.
     */
    class HttpsServer {
    public:
        HttpsServer(boost::asio::io_context& ioContext_,
                    Port port_,
                    std::shared_ptr<ApplicationConfig>& config_,
                    std::shared_ptr<RequestDispatcher>& requestDispatcher_);

    private:
        boost::asio::ssl::context sslContext;
        boost::asio::ip::tcp::acceptor acceptor;

        std::shared_ptr<ApplicationConfig> config;
        std::shared_ptr<RequestDispatcher> requestDispatcher;

        void accept();

        std::string getSslPassword();
    };
}
