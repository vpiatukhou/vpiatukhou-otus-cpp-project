#include "TcpConnection.h"

#include <iostream>
#include <utility>

namespace WebServer {

    namespace {
        namespace http = boost::beast::http;
    }

    //TODO should we use && reference instead of & here?
    TcpConnection::TcpConnection(boost::asio::ip::tcp::socket& socket_) : socket(std::move(socket_)) {
    }
   
    void TcpConnection::listen() {
        //pass "self" to the callback in order to keep the instance of TcpConnection alive while the connection exists
        auto self = shared_from_this();
        auto requestHandler = [this, self](boost::system::error_code const& error, std::size_t bytesTransferred) {
            //TODO handle error
            std::cout << "Accepted connection" << std::endl; //TODO remove

            http::response<http::string_body> response;
            response.version(11);
            response.result(http::status::ok);
            response.set(http::field::server, "WebServer"); //TODO take name from application.yaml

            //requestDispatcher.dispatch(request, response);

            response.prepare_payload();

            //auto writeHandler = [](boost::system::error_code const& error, std::size_t bytesTransferred) {
                //std::cout << "Response was sent" << std::endl;
                //std::cerr << "Error writing response." << std::endl; //add error handling
            //};

            //http::async_write(socket, res, writeHandler);
            boost::system::error_code errorCode;
	        http::write(socket, response, errorCode); //TODO do we need async_write here?
        };

        http::async_read(socket, buffer, request, requestHandler);
    }
}

