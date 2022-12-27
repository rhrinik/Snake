#include "Game.h"

void Game::run() {
    if (!running) {
        running = true;
        start = std::chrono::high_resolution_clock::now();
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    start = finish;

    gfx.beginFrame();
    update(elapsed.count());
    draw();
    gfx.endFrame();
}

void Game::draw() {
    gfx.drawCircle(gfx.getMouseCoord().first, gfx.getMouseCoord().second, 20, 100, 250, 50);
}

void Game::update(double dt) {
    count += dt;
    if (count > 1) {
        std::cout << count << " :: count" << std::endl;
        count -= 1;
        using namespace std::chrono_literals;
        std::int32_t x;
        std::string s = "message: ";
        std::mt19937 rng{std::random_device{}()};
        std::uniform_int_distribution dist(1, 100);
        sf::Packet packet;
        packet << s << dist(rng);
        server.send(packet);
    }
}

bool Game::isRunning() const {
    return running;
}
