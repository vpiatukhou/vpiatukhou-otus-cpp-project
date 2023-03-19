#pragma once

#include "Port.h"

#include <string>
#include <memory>

namespace WebServer {

    /**
     * Provides access to a configuration of the application.
     */
    class ApplicationConfig {
    public:
        ApplicationConfig(const std::string& configFilepath_);
        ApplicationConfig(const ApplicationConfig&) = delete;
        ApplicationConfig(ApplicationConfig&&) = delete;
        ~ApplicationConfig() = default;

        ApplicationConfig& operator=(const ApplicationConfig&) = delete;
        ApplicationConfig& operator=(ApplicationConfig&&) = delete;

        Port getServerPort() const;
        const std::string& getServerName() const;

        bool isSslEnabled() const;
        const std::string& getSslCertificatePath() const;
        const std::string& getSslPrivateKeyPath() const;
        const std::string& getSslPassword() const;
        const std::string& getSslDhFile() const;

        const std::string& getStaticResouceRootDir() const;
        const std::string& getNotFoundPage() const;

    private:
        static const Port DEFAULT_PORT;
        static const std::string DEFAULT_SERVER_NAME;
        static const bool DEFAULT_SSL_ENABLED;
        static const std::string DEFAULT_STATIC_RESOURCE_DIR;
        static const std::string DEFAULT_NOT_FOUND_PAGE;

        Port port = DEFAULT_PORT;
        std::string serverName = DEFAULT_SERVER_NAME;

        bool sslEnabled = DEFAULT_SSL_ENABLED;
        std::string sslCertificatePath;
        std::string sslPrivateKeyPath;
        std::string sslPassword;
        std::string sslDhFile;

        std::string staticResouceRootDir = DEFAULT_STATIC_RESOURCE_DIR;
        std::string notFoundPage = DEFAULT_STATIC_RESOURCE_DIR + DEFAULT_NOT_FOUND_PAGE;
    };

    using ApplicationConfigPtr = std::shared_ptr<ApplicationConfig>;

}
