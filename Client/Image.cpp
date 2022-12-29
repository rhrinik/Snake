#include "Image.h"

bool Image::loadFromFile(std::string const& path) {
    if (!texture.loadFromFile(path))
        return false;
    sprite.setTexture(texture);
    return true;
}
