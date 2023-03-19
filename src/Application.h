#pragma once

#include <memory>

namespace WebServer {

    class Application {
    public:
        Application();
        Application(const Application&) = delete;
        Application(Application&&) = default; //TODO test move constructor
        ~Application();

        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;

        void start(int argc, char* argv[]);
    private:
        class Impl;
        std::unique_ptr<Impl> impl;
    };
}
