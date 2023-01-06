#pragma once
#include <SFML/Graphics.hpp>
#include "Font.h"
#include "Color.h"

class Text {
    friend class Graphics;
    sf::Text text;
public:
    Text() = default;
    void setFont(const Font& newFont);
    virtual void setText(std::string const& str);
    void setSize(std::size_t size);
    void setOutlineColor(Color color);
    void setOutlineSize(std::size_t size);
    void setPosition(std::pair<int,int> pos);
    [[nodiscard]] std::pair<int,int> getPosition() const;
    [[nodiscard]] std::pair<int,int> getSize() const;
};
