#include "ProgramOptions.h"

#include <boost/program_options.hpp>

#include <iostream>
#include <stdexcept>

namespace WebServer {

    namespace {
        const std::string HELP_PARAM = "help";
        const std::string DEFAULT_CONFIG_FILEPATH = "/etc/webserver/config/application.json";
    }

    bool ProgramOptions::parse(int argc, char* argv[]) {
        namespace po = boost::program_options;

        auto configOption = po::value<std::string>(&configFilepath)->default_value(DEFAULT_CONFIG_FILEPATH);

        po::options_description optionsDescription("Options");
        optionsDescription.add_options()
            ("help,h", "Print help information.")
            ("config,c", configOption, "A path to the config file.\n");

        po::variables_map optionValues;

        try {
            po::store(po::parse_command_line(argc, argv, optionsDescription), optionValues);
        } catch (const po::error& e) {
            using namespace std::string_literals;
            throw std::invalid_argument("Error parsing command line: "s + e.what());//TODO should provide more specific exception?
        }

        po::notify(optionValues);

        //TODO do we need HELP at all if the application is a library?
        if (optionValues.count(HELP_PARAM)) {
            std::cout << "Usage:\n\twebserver [-c PATH_TO_CONFIG]\n\n" << optionsDescription << std::endl;
            return false;
        }

        return true;
    }

    const std::string& ProgramOptions::getConfigFilepath() const {
        return configFilepath;
    }
};