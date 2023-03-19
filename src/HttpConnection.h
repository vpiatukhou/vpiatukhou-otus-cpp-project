#pragma once

#include "RequestDispatcher.h"

#include <boost/asio.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/core/flat_buffer.hpp>

#include <memory>
#include <iostream>
#include <utility>

namespace WebServer {

    template<class Socket>
    class HttpConnection : public std::enable_shared_from_this<HttpConnection<Socket>> {
    public:
        HttpConnection(Socket& socket_,
                       ApplicationConfigPtr config_,
                       RequestDispatcherPtr requestDispatcher_)
                       : socket(std::move(socket_)), config(config_), requestDispatcher(requestDispatcher_) {
        }

        void listen() {
            //pass "self" to the callback in order to keep the instance of TcpConnection alive while the connection exists
            auto self = this->shared_from_this();
            auto requestHandler = [this, self](boost::system::error_code const& error, std::size_t bytesTransferred) {
                namespace http = boost::beast::http;

                if (error) {
                    std::cerr << "Error reading the request." << std::endl;
                } else {
                    std::cout << "Accepted connection." << std::endl; //TODO remove

                    http::response<http::string_body> response;
                    response.version(HTTP_VERSION);
                    response.result(http::status::ok); //TODO do we need to set status here?
                    response.set(http::field::server, config->getServerName());

                    requestDispatcher->dispatch(request, response);

                    response.prepare_payload();

                    //auto writeHandler = [](boost::system::error_code const& error, std::size_t bytesTransferred) {
                        //std::cout << "Response was sent" << std::endl;
                        //std::cerr << "Error writing response." << std::endl; //add error handling
                    //};

                    //http::async_write(socket, res, writeHandler);
                    boost::system::error_code errorCode;
                    http::write(socket, response, errorCode); //TODO do we need async_write here?
                }
            };

            boost::beast::http::async_read(socket, buffer, request, requestHandler);
        }

    protected:
        Socket socket;

    private:
        const unsigned int HTTP_VERSION = 11;

        boost::beast::flat_buffer buffer;
        boost::beast::http::request<boost::beast::http::string_body> request;

        ApplicationConfigPtr config;
        RequestDispatcherPtr requestDispatcher;
    };

}
