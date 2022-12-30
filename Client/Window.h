#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Window {
public:
    friend class Graphics;
    enum Keys { Up, Down, Left, Right, NumKeys };
private:
    bool keys[NumKeys]{};
    std::unique_ptr<sf::RenderWindow> wnd;
    bool windowClosed{true};
public:
    Window() = default;
    void createWindow(int width, int height, std::string const& title) {
        windowClosed = false;
        wnd = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title);
    }
    [[nodiscard]] bool const* getKeys() const {
        return keys;
    }
    void closeWindow();
    [[nodiscard]] bool isWindowClosed() const;
    void processEvents();
};
