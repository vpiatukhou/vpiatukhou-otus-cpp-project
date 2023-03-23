#include "Application.h"
#include "Resources.h"
#include "MediaType.h"
#include "HttpRequestResponse.h"

#include "gtest/gtest.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <chrono>
#include <fstream>
#include <string>
#include <thread>

namespace {
    using namespace WebServer;

    using namespace std::chrono_literals;
    using namespace std::string_literals;

    namespace http = boost::beast::http;
    namespace beast = boost::beast;
    using tcp = boost::asio::ip::tcp;

    const std::string TEST_DATA_DIR = BINARY_DIR + "/resources/"s;
    const std::string WEB_CONTENT_DIR = TEST_DATA_DIR + "web_content/";

    const std::string APPLICATION_CONFIG_ARG = "-c" + TEST_DATA_DIR + "config/application.json"s;
    const std::string REQUEST_TARGET = "/base_dir/foo.html";
    const auto WAIT_FOR_SERVER_START = 1s; 

    const std::string SERVER_HOST = "127.0.0.1";
    const std::string SERVER_PORT = "8080";
    const int HTTP_VERSION = 11;

    void sendRequest(const HttpRequest& request, HttpResponse& response) {
        boost::asio::io_context ioContext;

        tcp::resolver resolver(ioContext);
        beast::tcp_stream stream(ioContext);

        tcp::resolver::query query(SERVER_HOST, SERVER_PORT);
        auto const results = resolver.resolve(query);
        stream.connect(results);

        //send request
        http::write(stream, request);

        //receive response
        beast::flat_buffer buffer;
        http::read(stream, buffer, response);

        stream.socket().shutdown(tcp::socket::shutdown_both);
    }

    std::string getTestResource() {
        std::string expected;
        std::ifstream resource(WEB_CONTENT_DIR + REQUEST_TARGET, std::ios::binary | std::ios::ate);
        auto fileSize = resource.tellg();
        expected.resize(fileSize, '\0');
        resource.seekg(0);
        resource.read(expected.data(), fileSize);
        return expected;
    }
}

TEST(HttpServerApplicationTest, positive) {
    //given
    std::string configArg = APPLICATION_CONFIG_ARG;
    std::vector<char*> argv = { nullptr, configArg.data() };

    Application application;

    std::thread serverThread([&application, &argv](){
        application.start(2, argv.data());
    });

    //TODO stop application, otherwise the thread will continue running until all tests are passed
    serverThread.detach();

    //sleep for one sec to make sure that the server is up and running
    std::this_thread::sleep_for(WAIT_FOR_SERVER_START);

    //when
    HttpRequest request{http::verb::get, REQUEST_TARGET, HTTP_VERSION};
    request.set(http::field::host, SERVER_HOST);
    request.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    HttpResponse response;

    sendRequest(request, response);

    //then
    auto expected = getTestResource();
    ASSERT_EQ(expected, response.body());
}
