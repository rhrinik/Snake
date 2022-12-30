#include "Graphics.h"

void Graphics::beginFrame() {
    wnd.wnd->clear(sf::Color::Black);
}

void Graphics::endFrame() {
    wnd.wnd->display();
}

void Graphics::drawImage(Image &image) {
    image.sprite.setScale(
            static_cast<float>(wnd.wnd->getSize().x) / image.sprite.getLocalBounds().width,
            static_cast<float>(wnd.wnd->getSize().y) / image.sprite.getLocalBounds().height);
    wnd.wnd->draw(image.sprite);
}

void Graphics::drawText(Text &text) {
    wnd.wnd->draw(text.text);
}
