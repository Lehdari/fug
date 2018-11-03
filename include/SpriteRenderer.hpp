#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include "PhysicsComponent.hpp"
#include "SpriteComponent.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics/Sprite.hpp>

TECS_SYSTEM(SpriteRenderer, PhysicsComponent, SpriteComponent) {
    SpriteRenderer(sf::RenderWindow& window) : window(window) { };
    void operator()(PhysicsComponent& phys, SpriteComponent &sprite)
    {
        sprite.sprite.setPosition(phys.pos(0), phys.pos(1));
        window.draw(sprite.sprite);
    }
    sf::RenderWindow& window;
};

#endif
