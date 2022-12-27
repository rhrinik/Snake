#include "Game.h"

void Game::run() {
    gfx.beginFrame();
    update();
    draw();
    gfx.endFrame();
}

void Game::draw() {
    gfx.drawCircle(gfx.getMouseCoord().first, gfx.getMouseCoord().second, 20, 100, 250, 50);
}

void Game::update() {
    if (!stopwatch.removeTime(1))
        return;

    std::int32_t x;
    std::string s = "message: ";
    sf::Packet packet;
    packet << s << rand() % 100;
    server.send(packet);
    std::cout << "Message sent" << std::endl;
}

bool Game::init() {
    sf::Socket::Status status = server.connect("127.0.0.1", 53000);
    if (status != sf::Socket::Done) {
        std::cerr << "Connection failure." << std::endl;
        return false;
    }
    stopwatch.reset();
    return running = true;
}

bool Game::isRunning() const {
    return running;
}
