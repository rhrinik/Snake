#include "Application.h"

Application &Application::getInstance() {
    static Application app;
    return app;
}

void Application::run() {
    gfx.createWindow();
    game.init();
    while (!gfx.isWindowClosed() && game.isRunning()) {
        gfx.processWindowEvents();
        game.run();
    }
    gfx.closeWindow();
}