#pragma once

#include "RequestDispatcher.h"
#include "MediaType.h"

#include <boost/asio.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/core/flat_buffer.hpp>

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

namespace WebServer {

    namespace {
        const std::string INTERNAL_SERVER_ERROR_RESPONSE = "500 Internal Server Error";
    }

    /**
     * An HTTP connection. Receives HTTP requests and writes the responses.
     * The instance of this class is created when a client sets up a new connection 
     * and destroyed after the connection is closed.
     */
    template<class Socket>
    class HttpConnection : public std::enable_shared_from_this<HttpConnection<Socket>> {
    public:
        HttpConnection(Socket& socket_, ApplicationConfigPtr config_, RequestDispatcherPtr requestDispatcher_)
                       : socket(std::move(socket_)), config(config_), requestDispatcher(requestDispatcher_) {
        }

        /**
         * Reads the current HTTP request asynchronously. Calls RequestDispatcher. Writes the response.
         * 
         * The method doesn't block the current thread.
         */
        void listen() {
            namespace http = boost::beast::http;

            //pass "self" to the callback in order to keep the instance alive while the connection exists
            auto self = this->shared_from_this();
            auto requestHandler = [this, self](boost::system::error_code const& error, std::size_t) {
                if (error) {
                    std::cerr << "Error reading the request." << std::endl;
                } else {
                    std::cout << "Accepted the connection." << std::endl; //TODO remove

                    response.version(HTTP_VERSION);
                    response.result(http::status::ok);
                    response.set(http::field::server, config->getServerName());

                    try {
                        requestDispatcher->dispatch(request, response);
                    } catch (const std::exception& e) {
                        //TODO handle internal error
                        std::cerr << "Error processing the request: " << e.what() << std::endl;
                        response.result(http::status::internal_server_error);
                        response.set(http::field::content_type, MEDIA_TYPE_TEXT_PLAIN);
                        response.body() = INTERNAL_SERVER_ERROR_RESPONSE;
                    }

                    response.prepare_payload();

                    sendResponse();
                }
            };

            http::async_read(socket, buffer, request, requestHandler);
        }

    protected:
        Socket socket;

    private:
        const unsigned int HTTP_VERSION = 11;

        boost::beast::flat_buffer buffer;
        HttpRequest request;
        HttpResponse response;

        ApplicationConfigPtr config;
        RequestDispatcherPtr requestDispatcher;

        void sendResponse() {
            //pass "self" to the callback in order to keep the instance alive while the connection exists
            auto self = this->shared_from_this();
            auto writeHandler = [this, self](boost::system::error_code const& error, std::size_t) {
                std::cout << "Sent the response." << std::endl; //TODO remove
                if (error) {
                    std::cerr << "Error writing response." << std::endl;
                }
            };

            boost::beast::http::async_write(socket, response, writeHandler);
        }
    };

}
