#include "Application.h"

Application &Application::getInstance() {
    static Application app;
    return app;
}

void Application::run() {
    game.init();
    while (game.isRunning())
        game.run();
}