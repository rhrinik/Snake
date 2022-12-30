#include "Font.h"

bool Font::loadFontFromFile(const std::string &path) {
    return font.loadFromFile(path);
}

