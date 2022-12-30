#include "Text.h"

bool Text::loadFontFromFile(const std::string &path) {
    if (!font.loadFromFile(path))
        return false;
    text.setFont(font);
    return true;
}

void Text::setText(const std::string &str) {
    text.setString(str);
}

void Text::setSize(std::size_t size) {
    text.setCharacterSize(size);
}

void Text::setPosition(std::pair<int, int> pos) {
    text.setPosition(static_cast<float>(pos.first),static_cast<float>(pos.second));
}