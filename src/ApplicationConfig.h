#pragma once

#include "Port.h"

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace WebServer {

    struct MediaTypeMapping {
        std::string fileRegExp;
        std::string mediaType;
    };

    /**
     * Holds the configuration of the application.
     *
     * ATTENTION: the SSL password is CACHED in memory.
     */
    class ApplicationConfig {
    public:
        ApplicationConfig(const std::string& configFilepath_);
        ApplicationConfig(const ApplicationConfig&) = delete;
        ApplicationConfig(ApplicationConfig&&) = delete;
        ~ApplicationConfig() = default;

        ApplicationConfig& operator=(const ApplicationConfig&) = delete;
        ApplicationConfig& operator=(ApplicationConfig&&) = delete;

        /**
         * @return the port, the server is listening on.
         */
        Port getServerPort() const;

        /**
         * @return the value which is returned in "Server" header in a HTTP response.
         */
        const std::string& getServerName() const;

        /**
         * @return TRUE if SSL is enabled.
         */
        bool isSslEnabled() const;

        /**
         * @return a path to the SSL certificate file. The path is normalized (please see https://en.cppreference.com/w/cpp/filesystem/path).
         */
        const std::filesystem::path& getSslCertificatePath() const;

        /**
         * @return a path to the private key file. The path is normalized (please see https://en.cppreference.com/w/cpp/filesystem/path).
         */
        const std::filesystem::path& getSslPrivateKeyPath() const;

        /**
         * @return a path to the DH file. The path is normalized (please see https://en.cppreference.com/w/cpp/filesystem/path).
         */
        const std::filesystem::path& getSslDhFilepath() const;

        /**
         * @return the certificate's pass phrase.
         *         ATTENTION: the password is CACHED in memory.
         */
        const std::string& getSslPassword() const;

        /**
         * 
         */
        const std::filesystem::path& getStaticResouceRootDir() const;
        const std::filesystem::path& getNotFoundPage() const;

        const std::vector<MediaTypeMapping>& getMediaTypeMapping() const;

    private:
        Port port = 0;
        std::string serverName;

        bool sslEnabled = false;
        std::filesystem::path sslCertificatePath;
        std::filesystem::path sslPrivateKeyPath;
        std::string sslPassword;
        std::filesystem::path sslDhFilepath;

        std::filesystem::path staticResouceRootDir;
        std::filesystem::path notFoundPage;

        std::vector<MediaTypeMapping> mediaTypeMapping;
    };

    using ApplicationConfigPtr = std::shared_ptr<ApplicationConfig>;

}
