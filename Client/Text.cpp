#include "Text.h"

void Text::setText(const std::string &str) {
    text.setString(str);
}

void Text::setSize(std::size_t size) {
    text.setCharacterSize(size);
}

void Text::setPosition(std::pair<int, int> pos) {
    text.setPosition(static_cast<float>(pos.first),static_cast<float>(pos.second)-text.getGlobalBounds().top);
}

std::pair<int, int> Text::getSize() const {
    return {text.getGlobalBounds().width, text.getGlobalBounds().height};
}

void Text::setFont(const Font& newFont) {
    text.setFont(newFont.font);
}
