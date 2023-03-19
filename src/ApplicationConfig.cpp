#include "ApplicationConfig.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <string>

namespace {
    namespace pt = boost::property_tree;
}

namespace WebServer {

    namespace {
        const Port DEFAULT_PORT = 8080;
        const std::string DEFAULT_SERVER_NAME = "Web Server";
        const bool DEFAULT_SSL_ENABLED = false;
        const std::string EMPTY = "";
        const std::string DEFAULT_STATIC_RESOURCE_DIR = "/var/www/webserver";
        const std::string DEFAULT_NOT_FOUND_PAGE = "/pages/notFound.html";
    }

    ApplicationConfig::ApplicationConfig(const std::string& configFilepath_) {
        pt::ptree properties;
        pt::read_json(configFilepath_, properties);

        //TODO handle exceptions
        port = properties.get<Port>("serverPort", DEFAULT_PORT);
        serverName = properties.get<std::string>("serverName", DEFAULT_SERVER_NAME);
        sslEnabled = properties.get<bool>("ssl.enabled", DEFAULT_SSL_ENABLED);
        sslCertificatePath = properties.get<std::string>("ssl.certificateFilepath", EMPTY);
        sslPrivateKeyPath = properties.get<std::string>("ssl.privateKeyFilepath", EMPTY);
        sslDhFile = properties.get<std::string>("ssl.dhFilepath", EMPTY);
        //TODO is it safe to cache the password in memory?
        sslPassword = properties.get<std::string>("ssl.password", EMPTY);
        staticResouceRootDir = properties.get<std::string>("staticResourceMapping.rootDir", DEFAULT_STATIC_RESOURCE_DIR);
        notFoundPage = staticResouceRootDir + '/' + properties.get<std::string>("staticResourceMapping.notFoundPage", DEFAULT_NOT_FOUND_PAGE);
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

    const std::string& ApplicationConfig::getStaticResouceRootDir() const {
        return staticResouceRootDir;
    }

    const std::string& ApplicationConfig::getNotFoundPage() const {
        return notFoundPage;
    }
}
