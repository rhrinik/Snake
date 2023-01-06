#pragma once
#include <SFML/Graphics.hpp>
#include "Color.h"
#include "Image.h"
#include "Text.h"
#include "Window.h"

class Graphics {
    Window& wnd;
public:
    explicit Graphics(Window &wnd) : wnd(wnd) {}
    void beginFrame();
    void endFrame();
    void drawCircle(std::pair<int,int> topLeftPoint, int radius, Color color);
    void drawImage(Image &image);
    void drawText(Text &text);
    void drawRectangle(std::pair<int,int> topLeftPoint, std::pair<int,int> bottomRightPoint, Color color);
};
