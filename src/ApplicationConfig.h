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
        ApplicationConfig();
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

        const std::string& getContentRootDir() const;
        const std::string& getNotFoundPage() const;

    private:
        Port port;
        std::string serverName;

        bool sslEnabled = true;
        std::string sslCertificatePath;
        std::string sslPrivateKeyPath;
        std::string sslPassword; //TODO probably we should not store password in memory. Instead, we should read it every time from disk
        std::string sslDhFile;

        std::string contentRootDir;
        std::string notFoundPage;
    };

}
