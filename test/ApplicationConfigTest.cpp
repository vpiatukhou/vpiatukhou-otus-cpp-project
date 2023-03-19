#include "ApplicationConfig.h"
#include "Resources.h"

#include "gtest/gtest.h"

#include <filesystem>

using namespace WebServer;

namespace {
    using namespace std::string_literals;

    const std::string ROOT_DIR = BINARY_DIR + "/resources/"s;
    const std::string EMPTY_APPLICATION_JSON_FILEPATH = ROOT_DIR + "emptyApplication.json"s;
    const std::string APPLICATION_JSON_FILEPATH = ROOT_DIR + "application.json"s;

    void verifyDefaultValues(const ApplicationConfig& config) {
        ASSERT_EQ(8080, config.getServerPort());
        ASSERT_EQ("Web Server", config.getServerName());
        ASSERT_EQ(false, config.isSslEnabled());
        ASSERT_EQ("", config.getSslCertificatePath());
        ASSERT_EQ("", config.getSslPrivateKeyPath());
        ASSERT_EQ("", config.getSslPassword());
        ASSERT_EQ("", config.getSslDhFile());
        ASSERT_EQ("/var/www/webserver/", config.getStaticResouceRootDir());
        ASSERT_EQ("/var/www/webserver/pages/notFound.html", config.getNotFoundPage());
    }
}

TEST(ApplicationConfigTest, noConfigFile) {
    //when
    ApplicationConfig config("");

    //then
    verifyDefaultValues(config);
}

TEST(ApplicationConfigTest, emptyConfigFile) {
    //given
    ASSERT_TRUE(std::filesystem::is_regular_file(EMPTY_APPLICATION_JSON_FILEPATH)) << "Invalid test data. The file '"
        << EMPTY_APPLICATION_JSON_FILEPATH << "' was not found.";

    //when
    ApplicationConfig config(EMPTY_APPLICATION_JSON_FILEPATH);

    //then
    verifyDefaultValues(config);
}

TEST(ApplicationConfigTest, readAllProperties) {
    //when
    ApplicationConfig config(APPLICATION_JSON_FILEPATH);

    //then
    ASSERT_EQ(8081, config.getServerPort());
    ASSERT_EQ("aaa", config.getServerName());
    ASSERT_EQ(true, config.isSslEnabled());
    ASSERT_EQ("/ssl/cert.pem", config.getSslCertificatePath());
    ASSERT_EQ("/ssl/certkey.key", config.getSslPrivateKeyPath());
    ASSERT_EQ("aaa123", config.getSslPassword());
    ASSERT_EQ("/ssl/aaa.pem", config.getSslDhFile());
    ASSERT_EQ("/root/dir/", config.getStaticResouceRootDir());
    ASSERT_EQ("/root/dir/error/aaa.html", config.getNotFoundPage());
}
