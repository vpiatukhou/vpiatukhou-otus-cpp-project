#include "ProgramOptions.h"

#include <stdexcept>

#include <boost/program_options.hpp>

namespace WebServer {

    namespace {
        const std::string HELP_PARAM = "help";
        const std::string DEFAULT_CONFIG_FILEPATH = "/app/src/resources/application.json"; //TODO provide correct path
    }

    bool ProgramOptions::parse(int argc, char* argv[], std::ostream& out) {
        namespace po = boost::program_options;

        auto configOption = po::value<std::string>(&configFilepath)->default_value(DEFAULT_CONFIG_FILEPATH);

        po::options_description optionsDescription("Options");
        optionsDescription.add_options()
            ("help,h", "Print help information.")
            ("config,c", configOption, "A path to the config file.\n");

        po::variables_map optionValues;

        try {
            po::store(po::parse_command_line(argc, argv, optionsDescription), optionValues);
        } catch (po::error& e) {
            using namespace std::string_literals;
            throw std::invalid_argument("Error parsing command line: "s + e.what());//TODO should provide more specific exception?
        }

        po::notify(optionValues);

        if (optionValues.count(HELP_PARAM)) {
            out << "Usage:\n\twebserver [-c PATH_TO_CONFIG]\n\n" << optionsDescription << std::endl;
            return false;
        }

        return true;
    }

    const std::string& ProgramOptions::getConfigFilepath() const {
        return configFilepath;
    }
};