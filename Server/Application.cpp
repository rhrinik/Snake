#include "Application.h"

Application &Application::getInstance() {
    static Application app;
    return app;
}

void Application::run() {
    game.init();
    game.run();
}