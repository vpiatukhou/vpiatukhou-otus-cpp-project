#include "ApplicationConfig.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <string>

namespace {
    namespace pt = boost::property_tree;
}

namespace WebServer {

    ApplicationConfig::ApplicationConfig(const std::string& configFilepath_) {
        pt::ptree properties;
        pt::read_json(configFilepath_, properties);

        //TODO provide default values
        //TODO handle exceptions
        port = properties.get<Port>("serverPort");
        serverName = properties.get<std::string>("serverName");
        sslEnabled = properties.get<bool>("ssl.enabled");
        sslCertificatePath = properties.get<std::string>("ssl.certificateFilepath");
        sslPrivateKeyPath = properties.get<std::string>("ssl.privateKeyFilepath");
        sslDhFile = properties.get<std::string>("ssl.dhFilepath");
        //TODO is it safe to cache the password in memory?
        sslPassword = properties.get<std::string>("ssl.password");
        staticResouceRootDir = properties.get<std::string>("staticResourceMapping.rootDir");
        notFoundPage = staticResouceRootDir + '/' + properties.get<std::string>("staticResourceMapping.notFoundPage");
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
