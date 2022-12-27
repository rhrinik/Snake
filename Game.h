#pragma once
#include "Graphics.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <optional>

class Game {
    Graphics& gfx;
public:
    explicit Game(Graphics &gfx) : gfx(gfx) {
        sf::Socket::Status status = server.connect("127.0.0.1", 53000);
        if (status != sf::Socket::Done) { /* error...*/ }
    }
    void run();
    void update(double dt);
    void draw();

    bool running{false};
    [[nodiscard]] bool isRunning() const;
    double count = 0.0;
    sf::TcpSocket server;
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
};
