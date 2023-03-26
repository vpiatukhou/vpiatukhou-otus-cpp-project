#include "FooController.h"
#include "MediaType.h"

#include <string>

namespace WebServer {

    void FooController::processRequest(HttpRequestHolder& requestHolder, HttpResponse& response) {
        namespace http = boost::beast::http;

        response.set(http::field::content_type, MEDIA_TYPE_TEXT_PLAIN);

        std::string body;

        switch (requestHolder.getRequest().method()) {
        case http::verb::get:
            body = "Foo - GET. Query parameters:\n";
            for (auto& keyValue : requestHolder.getQueryParameters()) {
                body += "name=" + keyValue.first + ", value=" + keyValue.second + "\n";
            }
            response.body() = body;
            break;
        case http::verb::post:
            body = "Foo - POST";
            response.result(http::status::created);
            break;
        case http::verb::put:
            body = "Foo - PUT";
            break;
        case http::verb::delete_:
            response.result(http::status::no_content);
            break;
        default:
            body = "Foo - method is not allowed";
            break;
        }

        response.body() = body;
    }

}
