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
                    ApplicationConfigPtr config_,
                    RequestDispatcherPtr requestDispatcher_);

    private:
        boost::asio::ssl::context sslContext;
        boost::asio::ip::tcp::acceptor acceptor;

        ApplicationConfigPtr config;
        RequestDispatcherPtr requestDispatcher;

        void accept();

        std::string getSslPassword();
    };
}
