#include "ApplicationConfig.h"

namespace WebServer {

    ApplicationConfig::ApplicationConfig() {
        //TODO read from file
        port = 8080;
        serverName = "Web Server";
        sslCertificatePath = "/etc/otus-webserver/ssl/otusproject.pem";
        sslPrivateKeyPath = "/etc/otus-webserver/ssl/otusproject.key";
        sslDhFile = "/etc/otus-webserver/ssl/dh4096.pem";
        sslPassword = "otusproject";
        contentRootDir = "/var/www/webserver-demo";
        notFoundPage = "/pages/notFound.html";
    }

    Port ApplicationConfig::getServerPort() const {
        return port;
    }

    const std::string& ApplicationConfig::getServerName() const {
        return serverName;
    }

    bool ApplicationConfig::isSslEnabled() const {
        return sslEnabled;
    }

    const std::string& ApplicationConfig::getSslCertificatePath() const {
        return sslCertificatePath;
    }

    const std::string& ApplicationConfig::getSslPassword() const {
        return sslPassword;
    }

    const std::string& ApplicationConfig::getSslPrivateKeyPath() const {
        return sslPrivateKeyPath;
    }

    const std::string& ApplicationConfig::getSslDhFile() const {
        return sslDhFile;
    }

    const std::string& ApplicationConfig::getContentRootDir() const {
        return contentRootDir;
    }

    const std::string& ApplicationConfig::getNotFoundPage() const {
        return notFoundPage;
    }
}
