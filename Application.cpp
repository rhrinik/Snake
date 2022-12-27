#include "Application.h"

Application &Application::getInstance() {
    static Application app;
    return app;
}

void Application::run() {
    gfx.createWindow();
    while (!gfx.isWindowClosed()) {
        gfx.processWindowEvents();
        game.run();
        if (!game.isRunning())
            break;
    }
    gfx.closeWindow();
}