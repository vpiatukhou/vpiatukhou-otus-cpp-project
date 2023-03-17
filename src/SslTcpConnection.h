#pragma once

#include "RequestDispatcher.h"

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/core/flat_buffer.hpp>

#include <memory>

namespace WebServer {

    /**
     * A TCP connection. Receives commands from a client and forwards them to CommandProcessingFacade.
     *
     * The connection stays open until the client breaks it.
     */
    class SslTcpConnection : public std::enable_shared_from_this<SslTcpConnection> {
    public:
        SslTcpConnection(boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_, 
                         std::shared_ptr<ApplicationConfig>& config_,
                         std::shared_ptr<RequestDispatcher>& requestDispatcher_);

        void doHandshake();
        void listen();

    private:
        boost::asio::ssl::stream<boost::asio::ip::tcp::socket> sslSocket;

        boost::beast::flat_buffer buffer;
        boost::beast::http::request<boost::beast::http::string_body> request;

        std::shared_ptr<ApplicationConfig> config;
        std::shared_ptr<RequestDispatcher> requestDispatcher;
    };

}
