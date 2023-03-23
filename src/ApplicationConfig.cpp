#include "ApplicationConfig.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include <filesystem>
#include <string>
#include <iostream>

namespace WebServer {

    namespace {
        using namespace std::literals::string_literals;

        namespace pt = boost::property_tree;
        namespace fs = std::filesystem;
        const auto EMPTY = ""s;

        const auto SERVER_PORT_PROPERTY = "serverPort"s;
        const auto SERVER_NAME_PROPERTY = "serverName"s;
        const auto SSL_ENABLED_PROPERTY = "ssl.enabled"s;
        const auto SSL_CERTIFICATE_FILEPATH_PROPERTY = "ssl.certificateFilepath"s;
        const auto SSL_PRIVATE_KEY_FILEPATH_PROPERTY = "ssl.privateKeyFilepath"s;
        const auto SSL_DH_FILEPATH_PROPERTY = "ssl.dhFilepath"s;
        const auto SSL_PASSWORD_FILEPATH_PROPERTY = "ssl.password"s;
        const auto STATIC_RESOURCE_ROOT_DIR_PROPERTY = "staticResourceMapping.rootDir"s;
        const auto NOT_FOUND_PAGE_PROPERTY = "staticResourceMapping.notFoundPage"s;
        const auto MEDIA_TYPE_MAPPING_PROPERTY = "mediaTypeMapping"s;
        const auto MEDIA_TYPE_MAPPING_FILE_NAME_PROPERTY = "fileNameRegex"s;
        const auto MEDIA_TYPE_MAPPING_TYPE_PROPERTY = "mediaType"s;

        const Port DEFAULT_PORT = 8080;
        const auto DEFAULT_SERVER_NAME = "Web Server"s;
        const bool DEFAULT_SSL_ENABLED = false;
        const auto DEFAULT_STATIC_RESOURCE_DIR = "/var/www/webserver/"s;
        const auto DEFAULT_NOT_FOUND_PAGE = "pages/notFound.html"s;
    }

    ApplicationConfig::ApplicationConfig(const std::string& configFilepath_) {
        std::cout << "Trying to read config '" << configFilepath_ << "'" << std::endl;

        if (fs::is_regular_file(configFilepath_)) {
            pt::ptree properties; //TODO replace ptree with iptree
            pt::read_json(configFilepath_, properties);

            //TODO handle exceptions
            port = properties.get<Port>(SERVER_PORT_PROPERTY, DEFAULT_PORT);
            serverName = properties.get<std::string>(SERVER_NAME_PROPERTY, DEFAULT_SERVER_NAME);
            sslEnabled = properties.get<bool>(SSL_ENABLED_PROPERTY, DEFAULT_SSL_ENABLED);
            sslCertificatePath = properties.get<std::string>(SSL_CERTIFICATE_FILEPATH_PROPERTY, EMPTY);
            sslPrivateKeyPath = properties.get<std::string>(SSL_PRIVATE_KEY_FILEPATH_PROPERTY, EMPTY);
            sslDhFilepath = properties.get<std::string>(SSL_DH_FILEPATH_PROPERTY, EMPTY);
            sslPassword = properties.get<std::string>(SSL_PASSWORD_FILEPATH_PROPERTY, EMPTY);

            //TODO append '/' if it is missed
            staticResouceRootDir = properties.get<std::string>(STATIC_RESOURCE_ROOT_DIR_PROPERTY, DEFAULT_STATIC_RESOURCE_DIR);
            staticResouceRootDir = fs::path(staticResouceRootDir).lexically_normal(); //TODO maybe better to use canonical?

            notFoundPage = properties.get<std::string>(NOT_FOUND_PAGE_PROPERTY, DEFAULT_NOT_FOUND_PAGE);
            if (notFoundPage.is_absolute()) {
                //TODO throw error
            }

            notFoundPage = staticResouceRootDir / fs::path(notFoundPage);
            notFoundPage = notFoundPage.lexically_normal();

            if (auto mappingNode = properties.get_child_optional(MEDIA_TYPE_MAPPING_PROPERTY)) {
                BOOST_FOREACH(pt::ptree::value_type const& value, *mappingNode) {
                    MediaTypeMapping mapping {
                        value.second.get<std::string>(MEDIA_TYPE_MAPPING_FILE_NAME_PROPERTY),
                        value.second.get<std::string>(MEDIA_TYPE_MAPPING_TYPE_PROPERTY)
                    };
                    mediaTypeMapping.push_back(mapping);
                }
            }
        } else {
            std::cout << "The application config '" << configFilepath_ << "' was not found. Default values will be used." << std::endl;

            port = DEFAULT_PORT;
            serverName = DEFAULT_SERVER_NAME;
            sslEnabled = DEFAULT_SSL_ENABLED;
            staticResouceRootDir = DEFAULT_STATIC_RESOURCE_DIR;
            notFoundPage = staticResouceRootDir / DEFAULT_NOT_FOUND_PAGE;
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

    const std::filesystem::path& ApplicationConfig::getSslCertificatePath() const {
        return sslCertificatePath;
    }

    const std::string& ApplicationConfig::getSslPassword() const {
        return sslPassword;
    }

    const std::filesystem::path& ApplicationConfig::getSslPrivateKeyPath() const {
        return sslPrivateKeyPath;
    }

    const std::filesystem::path& ApplicationConfig::getSslDhFilepath() const {
        return sslDhFilepath;
    }

    const std::filesystem::path& ApplicationConfig::getStaticResouceRootDir() const {
        return staticResouceRootDir;
    }

    const std::filesystem::path& ApplicationConfig::getNotFoundPage() const {
        return notFoundPage;
    }

    const std::vector<MediaTypeMapping>& ApplicationConfig::getMediaTypeMapping() const {
        return mediaTypeMapping;
    }
}
