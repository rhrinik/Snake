#include "Application.h"

Application &Application::getInstance() {
    static Application app;
    return app;
}

void Application::run() {
    gfx.createWindow(windowWidth, windowHeight, std::string(windowTitle));

    game.init(); //check for errors
    game.run();

    gfx.closeWindow();
}