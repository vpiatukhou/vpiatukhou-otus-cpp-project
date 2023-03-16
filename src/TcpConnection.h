#pragma once

#include "RequestDispatcher.h"

#include <boost/asio.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/core/flat_buffer.hpp>

#include <memory>

namespace WebServer {

    /**
     * A TCP connection. Receives commands from a client and forwards them to CommandProcessingFacade.
     *
     * The connection stays open until the client breaks it.
     */
    class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
    public:
        TcpConnection(boost::asio::ip::tcp::socket& socket_);

        void listen();

    private:
        boost::asio::ip::tcp::socket socket;

        boost::beast::flat_buffer buffer;
        boost::beast::http::request<boost::beast::http::string_body> request;

        //RequestDispatcher requestDispatcher;
    };

}
