#pragma once

#include <filesystem>
#include <string>

namespace WebServer {

    std::string removeQueryString(const std::string& url);

    bool checkIfPathStartsWithBase(const std::filesystem::path& filepath, const std::filesystem::path& base);

}