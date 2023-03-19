#include "HttpServer.h"
#include "HttpConnection.h"

#include <iostream>

namespace WebServer {

    namespace {
        using namespace boost::asio::ip;
    }

    HttpServer::HttpServer(boost::asio::io_context& ioContext_,
                           Port port_,
                           std::shared_ptr<ApplicationConfig>& config_,
                           std::shared_ptr<RequestDispatcher>& requestDispatcher_) :
        acceptor(ioContext_, tcp::endpoint(tcp::v4(), port_)), config(config_), requestDispatcher(requestDispatcher_) {

        accept();
    }

    void HttpServer::accept() {
        acceptor.async_accept([this](boost::system::error_code error, boost::asio::ip::tcp::socket socket) {
            if (error) {
                std::cerr << "Error accepting request. Code: " << error << " Message: " << error.message() << std::endl;
            } else {
                //Make a shared pointer in order to allow usage enable_shared_from_this in TcpConnection.
                //The instance of HttpConnection won't be deleted when "accept()" returns control because
                //the pointer to it will be "captured" in HttpConnection::listen().
                std::make_shared<HttpConnection<boost::asio::ip::tcp::socket>>(socket, config, requestDispatcher)->listen();

                //start listening for a next incoming connection
                accept();
            }

            });
    }

}