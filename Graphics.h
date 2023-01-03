#pragma once

#include <SFML/Graphics.hpp>
#include <tuple>

class Graphics {
    std::unique_ptr<sf::RenderWindow> wnd;
public:
    void beginFrame();

    void createWindow(int width, int height, std::string const &title);

    void closeWindow();

    void endFrame();

    [[nodiscard]] bool isWindowOpen() const;

    void processWindowEvents();

    void drawSnake(float x, float y);

    void drawFood(float x, float y);

    char getKP();
};
