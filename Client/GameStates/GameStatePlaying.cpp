#include "GameStatePlaying.h"

GameState::States GameStatePlaying::runState(States previous) {
    if (wnd.isWindowClosed())
        return End;
    if (previous != Playing)
        init();

    update();
    draw();

    return Playing;
}

void GameStatePlaying::updateState() {
    /*auto it = std::find(wnd.getKeys(), wnd.getKeys() + Window::Keys::NumKeys, true);
    if (it != wnd.getKeys() + Window::Keys::NumKeys)
        snake.setDirection(static_cast<Snake::Direction>(std::distance(wnd.getKeys(),it)));*/

    if (stopwatchGameSpeed.removeTime(0.1))
        snake.move();

    if (food.getCoords() == snake.getSegments()[0]) {
        snake.grow();
        food.reposition({2000,1500});
    }
    if (snake.wallCollision({0,0},{2000,1500}) || snake.selfCollision())
        std::cout << "OUCH" << std::endl;

    /*std::int32_t x;
    std::string s = "message: ";
    sf::Packet packet;
    packet << s << rand() % 100;
    server.send(packet);
    std::cout << "Message sent" << std::endl;*/
}

void GameStatePlaying::drawState() {
    snake.draw(gfx);
    food.draw(gfx);
    //gfx.drawCircle(gfx.getMouseCoord().first, gfx.getMouseCoord().second, 20, Color(100, 250, 50));
}

void GameStatePlaying::initState() {
    //sf::Socket::Status status = server.connect("127.0.0.1", 53000);
    //if (status != sf::Socket::Done)
    stopwatchGameSpeed.reset();
    stopwatch.reset();
    wnd.registerObject(*this);
}

void GameStatePlaying::onKeyUp() {
    snake.setDirection(Snake::Direction::Up);
}

void GameStatePlaying::onKeyDown() {
    snake.setDirection(Snake::Direction::Down);
}

void GameStatePlaying::onKeyLeft() {
    snake.setDirection(Snake::Direction::Left);
}

void GameStatePlaying::onKeyRight() {
    snake.setDirection(Snake::Direction::Right);
}

void GameStatePlaying::onKeyEnter() {
}
