#include "Application.h"
#include "Constants.h"

Application &Application::getInstance() {
    static Application app;
    return app;
}

void Application::run() {
    gfx.createWindow(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, std::string(windowTitle));
    // game.init();
    while (gfx.isWindowOpen() /*&& game.isRunning()*/) {
        gfx.processWindowEvents();
        game.run();
    }
    gfx.closeWindow();
}