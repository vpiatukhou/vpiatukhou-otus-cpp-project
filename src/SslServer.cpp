#include "SslServer.h"
#include "SslTcpConnection.h"

#include <iostream>

namespace WebServer {

    namespace {
        using namespace boost::asio::ip;
    }

    SslServer::SslServer(boost::asio::io_context& ioContext_, 
                         Port port_,
                         std::shared_ptr<ApplicationConfig>& config_, //TODO do we need '&' ?
                         std::shared_ptr<RequestDispatcher>& requestDispatcher_) :
        sslContext(boost::asio::ssl::context::sslv23),
        acceptor(ioContext_, tcp::endpoint(tcp::v4(), port_)),
        config(config_),
        requestDispatcher(requestDispatcher_) {

        sslContext.set_options(boost::asio::ssl::context::default_workarounds
            | boost::asio::ssl::context::no_sslv2
            | boost::asio::ssl::context::single_dh_use);
        sslContext.set_password_callback(std::bind(&SslServer::getSslPassword, this));
        sslContext.use_certificate_chain_file(config_->getSslCertificatePath());
        sslContext.use_private_key_file(config_->getSslPrivateKeyPath(), boost::asio::ssl::context::pem);
        sslContext.use_tmp_dh_file(config_->getSslDhFile());

        accept();
    }

    void SslServer::accept() {
        acceptor.async_accept([this](boost::system::error_code error, boost::asio::ip::tcp::socket socket) {
            if (error) {
                std::cerr << "Error accepting request. Code: " << error << " Message: " << error.message() << std::endl;
            } else {
                //Make a shared pointer in order to allow usage enable_shared_from_this in TcpConnection.
                //The instance of TcpConnection won't be deleted when "accept()" returns control because
                //the pointer to it will be "captured" in TcpConnection::listen().
                std::make_shared<SslTcpConnection>(
                    boost::asio::ssl::stream<tcp::socket>(std::move(socket), sslContext),
                    config,
                    requestDispatcher)->doHandshake();

                //start listening for a next incoming connection
                accept();
            }

            });
    }

    std::string SslServer::getSslPassword(){ //TODO do we need this method?
        return config->getSslPassword();
    }
}