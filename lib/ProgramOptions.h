#pragma once

#include <string>

namespace WebServer {

    /**
     * Parses the given program options.
     */
    class ProgramOptions {
    public:
        /**
         * Parses the given arguments.
         * 
         * If the input is invalid, prints help information in the standard output.
         * 
         * @param argc - a number of arguments. It is the first argument of the function 'int main(argc, argv)'.
         * @param argv - the program arguments. It is the second argument of the function 'int main(argc, argv)'.
         * @return TRUE if the arguments have been correctly parsed.
         *         FALSE otherwise. Help information has been printed in the standard output in this case.
         */
        bool parse(int argc, char* argv[]);

        const std::string& getConfigFilepath() const;

    private:
        std::string configFilepath;

    };

}
