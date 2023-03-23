#include "UrlUtil.h"

#include <algorithm>

namespace WebServer {

    namespace {
        const char QUERY_BEGIN_MARK = '?';
    }

    std::string removeQueryString(const std::string& url) {
        auto queryParamPosition = url.find_first_of(QUERY_BEGIN_MARK);
        return queryParamPosition == std::string::npos ? url : url.substr(0, queryParamPosition);
    }

    bool checkIfPathStartsWithRoot(const std::filesystem::path& filepath, const std::filesystem::path& root) {
        auto[filepathIt, rootIt] = std::mismatch(filepath.begin(), filepath.end(), root.begin(), root.end());
        return rootIt == root.end() || *rootIt == ""; /* the iterator points to an empty element 
                                                         if the last element is a directory separator.
                                                         Please see https://en.cppreference.com/w/cpp/filesystem/path/begin */
    }

}