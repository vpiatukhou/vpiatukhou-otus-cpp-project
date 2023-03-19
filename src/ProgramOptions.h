#pragma once

#include <ostream>

namespace WebServer {

    class ProgramOptions {
    public:
        bool parse(int argc, char* argv[], std::ostream& out);

        const std::string& getConfigFilepath() const;

    private:
        std::string configFilepath;

    };

}
