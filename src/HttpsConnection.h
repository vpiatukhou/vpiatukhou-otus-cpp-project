#pragma once

#include "HttpConnection.h"

#include <boost/asio/ssl.hpp>

#include <memory>

namespace WebServer {

    /**
     * A TCP connection. Receives commands from a client and forwards them to CommandProcessingFacade.
     *
     * The connection stays open until the client breaks it.
     */
    class HttpsConnection : public HttpConnection<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> {
    public:
        HttpsConnection(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>&& socket_,
                        std::shared_ptr<ApplicationConfig>& config_,
                        std::shared_ptr<RequestDispatcher>& requestDispatcher_);

        void doHandshake();
    };

}
