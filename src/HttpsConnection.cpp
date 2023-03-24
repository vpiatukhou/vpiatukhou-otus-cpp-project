#include "HttpsConnection.h"

#include <iostream>

namespace WebServer {

    namespace {
        namespace http = boost::beast::http;

        const unsigned int HTTP_VERSION = 11;
    }

    HttpsConnection::HttpsConnection(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>&& socket_,
                                     ApplicationConfigPtr config_,
                                     RequestDispatcherPtr requestDispatcher_) 
        : HttpConnection<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>(socket_, config_, requestDispatcher_) {
    }

    void HttpsConnection::doHandshake() {
        auto self(shared_from_this());
        auto handshakeHandler = [this, self](const boost::system::error_code& error) {
            if (error) {
                std::cerr << "Unable to set up an HTTPS connection." << std::endl;
            } else {
                listen();
            }
        };

        socket.async_handshake(boost::asio::ssl::stream_base::server, handshakeHandler);
    }
}
