#include "Application.h"

Application &Application::getInstance() {
    static Application app;
    return app;
}

void Application::run() {
    gfx.createWindow(windowWidth, windowHeight, std::string(windowTitle));
    game.init();
    while (!gfx.isWindowClosed() && game.isRunning()) {
        gfx.processWindowEvents();
        game.run();
    }
    gfx.closeWindow();
}