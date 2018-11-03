#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include <SFML/Graphics/Sprite.hpp>

struct SpriteComponent {
    SpriteComponent(sf::Texture &texture, int colorIdx, int w, int h)
    {
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(colorIdx * w, 0, w, h));
    }
    sf::Sprite sprite;
};

#endif
