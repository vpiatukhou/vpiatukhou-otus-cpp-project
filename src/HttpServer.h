#pragma once

#include "Port.h"
#include "RequestDispatcher.h"

#include <boost/asio.hpp>

#include <memory>

namespace WebServer {

    /**
     * An asynchronous TCP server. Creates a new TcpConnection object for an each incoming connection.
     */
    class HttpServer {
    public:
        HttpServer(boost::asio::io_context& ioContext_, 
                   Port port_,
                   std::shared_ptr<ApplicationConfig>& config_,
                   std::shared_ptr<RequestDispatcher>& requestDispatcher_);

    private:
        boost::asio::ip::tcp::acceptor acceptor;

        std::shared_ptr<ApplicationConfig> config;
        std::shared_ptr<RequestDispatcher> requestDispatcher;

        void accept();
    };
}
