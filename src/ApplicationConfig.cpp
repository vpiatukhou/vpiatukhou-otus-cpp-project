#include "ApplicationConfig.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <filesystem>
#include <string>
#include <iostream>

namespace WebServer {

    namespace {
        namespace pt = boost::property_tree;
        const std::string EMPTY = "";

        const std::string SERVER_PORT_PROPERTY = "serverPort";
        const std::string SERVER_NAME_PROPERTY = "serverName";
        const std::string SSL_ENABLED_PROPERTY = "ssl.enabled";
        const std::string SSL_CERTIFICATE_FILEPATH_PROPERTY = "ssl.certificateFilepath";
        const std::string SSL_PRIVATE_KEY_FILEPATH_PROPERTY = "ssl.privateKeyFilepath";
        const std::string SSL_DH_FILEPATH_PROPERTY = "ssl.dhFilepath";
        const std::string SSL_PASSWORD_FILEPATH_PROPERTY = "ssl.password";
        const std::string STATIC_RESOURCE_ROOT_DIR_PROPERTY = "staticResourceMapping.rootDir";
        const std::string NOT_FOUND_PAGE_PROPERTY = "staticResourceMapping.notFoundPage";
    }

    const Port ApplicationConfig::DEFAULT_PORT = 8080;
    const std::string ApplicationConfig::DEFAULT_SERVER_NAME = "Web Server";
    const bool ApplicationConfig::DEFAULT_SSL_ENABLED = false;
    const std::string ApplicationConfig::DEFAULT_STATIC_RESOURCE_DIR = "/var/www/webserver/";
    const std::string ApplicationConfig::DEFAULT_NOT_FOUND_PAGE = "pages/notFound.html";

    ApplicationConfig::ApplicationConfig(const std::string& configFilepath_) {
        if (std::filesystem::is_regular_file(configFilepath_)) {
            pt::ptree properties;
            pt::read_json(configFilepath_, properties);

            //TODO handle exceptions
            port = properties.get<Port>(SERVER_PORT_PROPERTY, DEFAULT_PORT);
            serverName = properties.get<std::string>(SERVER_NAME_PROPERTY, DEFAULT_SERVER_NAME);
            sslEnabled = properties.get<bool>(SSL_ENABLED_PROPERTY, DEFAULT_SSL_ENABLED);
            sslCertificatePath = properties.get<std::string>(SSL_CERTIFICATE_FILEPATH_PROPERTY, EMPTY);
            sslPrivateKeyPath = properties.get<std::string>(SSL_PRIVATE_KEY_FILEPATH_PROPERTY, EMPTY);
            sslDhFile = properties.get<std::string>(SSL_DH_FILEPATH_PROPERTY, EMPTY);
            sslPassword = properties.get<std::string>(SSL_PASSWORD_FILEPATH_PROPERTY, EMPTY);
            staticResouceRootDir = properties.get<std::string>(STATIC_RESOURCE_ROOT_DIR_PROPERTY, DEFAULT_STATIC_RESOURCE_DIR);
            notFoundPage = staticResouceRootDir + properties.get<std::string>(NOT_FOUND_PAGE_PROPERTY, DEFAULT_NOT_FOUND_PAGE);
        } else {
            std::cout << "The application config '" << configFilepath_ << "' was not found. Default values are used." << std::endl;
        }
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
