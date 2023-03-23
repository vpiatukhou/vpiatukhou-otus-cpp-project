#pragma once

#include <filesystem>
#include <string>

namespace WebServer {

    std::string removeQueryString(const std::string& url);

    bool checkIfPathStartsWithRoot(const std::filesystem::path& filepath, const std::filesystem::path& root);

}