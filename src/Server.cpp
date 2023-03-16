#include "Server.h"
#include "TcpConnection.h"

#include <iostream>

namespace WebServer {

    namespace {
        using namespace boost::asio::ip;
    }

    Server::Server(boost::asio::io_context& ioContext_, Port port_, std::shared_ptr<RequestDispatcher>& requestDispatcher_) :
        acceptor(ioContext_, tcp::endpoint(tcp::v4(), port_)), requestDispatcher(requestDispatcher_) {

        accept();
    }

    void Server::accept() {
        acceptor.async_accept([this](boost::system::error_code error, boost::asio::ip::tcp::socket socket) {
            if (error) {
                std::cerr << "Error accepting request. Code: " << error << " Message: " << error.message() << std::endl;
            } else {
                //Make a shared pointer in order to allow usage enable_shared_from_this in TcpConnection.
                //The instance of TcpConnection won't be deleted when "accept()" returns control because
                //the pointer to it will be "captured" in TcpConnection::listen().
                std::make_shared<TcpConnection>(socket)->listen();

                //start listening for a next incoming connection
                accept();
            }

            });
    }

}