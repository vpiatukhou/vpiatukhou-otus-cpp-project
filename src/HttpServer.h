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
                   ApplicationConfigPtr config_,
                   RequestDispatcherPtr requestDispatcher_);

    private:
        boost::asio::ip::tcp::acceptor acceptor;

        ApplicationConfigPtr config;
        RequestDispatcherPtr requestDispatcher;

        void accept();
    };
}
