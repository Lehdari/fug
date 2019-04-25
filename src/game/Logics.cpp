//
// Created by Lehdari on 6.4.2019.
//

#include <game/Logics.hpp>
#include <game/PhysicsComponent.hpp>
#include <Ecs.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <sstream>


Logic_Ball::Logic_Ball(const EntityId& paddleId) :
    _paddleId       (paddleId),
    _followPaddle   (true)
{
}

void Logic_Ball::operator()(Ecs& ecs, const EntityId& eId)
{
    if (_followPaddle) {
        auto* myPc = ecs.getComponent<PhysicsComponent>(eId);
        auto* paddlePc = ecs.getComponent<PhysicsComponent>(_paddleId);
        myPc->pos.x = paddlePc->pos.x;
    }
}


void Logic_Paddle::operator()(Ecs& ecs, const EntityId& eId)
{
    auto* pc = ecs.getComponent<PhysicsComponent>(eId);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pc->pos.x > 32.0f)
        pc->pos.x -= 4.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pc->pos.x < 800.0f-32.0f)
        pc->pos.x += 4.0f;
}


sf::Font Logic_GameManager::__font = initFont();

Logic_GameManager::Logic_GameManager(
    sf::RenderWindow& window, sf::Texture& blockTexture) :
    _window         (window),
    _blockTexture   (blockTexture),
    _points         (0),
    _lives          (3)
{
    _text.setPosition(8.0f, 570.0f);
    _text.setFillColor(sf::Color::White);
    _text.setFont(__font);
    _text.setCharacterSize(20);
}

void Logic_GameManager::operator()(Ecs& ecs, const EntityId& eId)
{
    std::stringstream text;
    text << "Lives: " << _lives << "\tPoints: " << _points;
    _text.setString(text.str());
    _window.draw(_text);
}

sf::Font Logic_GameManager::initFont()
{
    sf::Font font;
    font.loadFromFile("../res/fonts/modeseven.ttf");
    return font;
}
