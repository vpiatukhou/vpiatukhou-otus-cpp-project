#pragma once

#include "HttpConnection.h"

#include <boost/asio/ssl.hpp>

#include <memory>

namespace WebServer {

    class HttpsConnection : public HttpConnection<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> {
    public:
        HttpsConnection(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>&& socket_,
                        ApplicationConfigPtr config_,
                        RequestDispatcherPtr requestDispatcher_);

        void doHandshake();
    };

}
