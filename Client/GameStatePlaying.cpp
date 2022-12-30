#include "GameStatePlaying.h"

GameState::States GameStatePlaying::runState(Window &wnd, Graphics &gfx) {
    if (wnd.isWindowClosed())
        return GameState::End;

    update(wnd);
    draw(gfx);

    return Playing;
}

void GameStatePlaying::updateState(Window &wnd) {
    auto it = std::find(wnd.getKeys(), wnd.getKeys() + Window::Keys::NumKeys, true);
    if (it != wnd.getKeys() + Window::Keys::NumKeys)
        snake.setDirection(static_cast<Snake::Direction>(std::distance(wnd.getKeys(),it)));

    if (stopwatchGameSpeed.removeTime(0.1))
        snake.move();

    if (food.getCoords() == snake.getSegments()[0]) {
        snake.grow();
        food.reposition({2000,1500});
    }

    /*std::int32_t x;
    std::string s = "message: ";
    sf::Packet packet;
    packet << s << rand() % 100;
    server.send(packet);
    std::cout << "Message sent" << std::endl;*/
}

void GameStatePlaying::drawState(Graphics &gfx) {
    snake.draw(gfx);
    food.draw(gfx);
    //gfx.drawCircle(gfx.getMouseCoord().first, gfx.getMouseCoord().second, 20, Color(100, 250, 50));
}

void GameStatePlaying::initState() {
    //sf::Socket::Status status = server.connect("127.0.0.1", 53000);
    //if (status != sf::Socket::Done)
    stopwatchGameSpeed.reset();
    stopwatch.reset();
}
