#include "Application.h"

Application &Application::getInstance() {
    static Application app;
    return app;
}

void Application::run(int argc, char *argv[]) {
    auto result = checkPort(argc, argv);
    if (!result.first)
        return;
    std::cout << "Starting server on port " << result.second << "......" << std::endl;
    game.init(result.second);
    game.run();
}

std::pair<bool, int> Application::checkPort(int argc, char *argv[]) {
    int port;
    if (argc > 1) {
        try {
            port = std::stoi(argv[1]);
        } catch (...) {
            std::cerr << "Bad port number. Please select a valid port for server to listen on." << std::endl;
            return {false, 0};
        }
        if (port > 65535 || port < 49152) {
            std::cerr << "Invalid port number." << std::endl;
            return {false, 0};
        }
        return {true,port};
    }
    std::cerr << "Usage: snakeServer PORT" << std::endl;
    return {false,port};
}