#pragma once

#include <memory>

namespace WebServer {

    /**
     * A class is used to set up and launch the server application.
     * 
     * Normally it is used in main() method like this:
     * 
     *   Application application;
     *   application.exec(argc, argv);
     */
    class Application {
    public:
        Application();
        Application(const Application&) = delete;
        Application(Application&&) = default;
        ~Application();

        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;

        /**
         * @param argc - a number of arguments. It is the first argument of the function 'int main(argc, argv)'.
         * @param argv - program arguments. It is the second argument of the function 'int main(argc, argv)'.
         */
        void start(int argc, char* argv[]);
    private:
        class Impl;
        std::unique_ptr<Impl> impl;
    };
}
