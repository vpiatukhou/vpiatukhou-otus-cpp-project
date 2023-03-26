#include "BarController.h"
#include "MediaType.h"

namespace WebServer {

    void BarController::processRequest(HttpRequestHolder& requestHolder, HttpResponse& response) {
        namespace http = boost::beast::http;

        response.set(http::field::content_type, MEDIA_TYPE_TEXT_PLAIN);

        switch (requestHolder.getRequest().method()) {
        case http::verb::get:
            response.body() = "Bar - GET";
            //the response status is OK by default
            break;
        case http::verb::post:
            response.body() = "Bar - POST";
            response.result(http::status::created);
            break;
        case http::verb::put:
            response.body() = "Bar - PUT";
            //the response status is OK by default
            break;
        case http::verb::delete_:
            response.result(http::status::no_content);
            break;
        default:
            response.body() = "Bar - method is not allowed";
            //the response status is OK by default
            break;
        }
    }

}
