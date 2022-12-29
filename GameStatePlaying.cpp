#include "GameStatePlaying.h"

GameState::States GameStatePlaying::runState(Graphics &gfx) {
    if (gfx.isWindowClosed())
        return GameState::End;

    update();
    draw(gfx);

    return Playing;
}

void GameStatePlaying::updateState() {
    if (!stopwatch.removeTime(1))
        return;

    snake.move();
    /*std::int32_t x;
    std::string s = "message: ";
    sf::Packet packet;
    packet << s << rand() % 100;
    server.send(packet);
    std::cout << "Message sent" << std::endl;*/
}

void GameStatePlaying::drawState(Graphics &gfx) {
    snake.draw(gfx);
    //gfx.drawCircle(gfx.getMouseCoord().first, gfx.getMouseCoord().second, 20, Color(100, 250, 50));
}

void GameStatePlaying::initState() {
    //sf::Socket::Status status = server.connect("127.0.0.1", 53000);
    //if (status != sf::Socket::Done)
    stopwatch.reset();
}
