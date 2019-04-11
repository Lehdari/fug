//
// Created by Lehdari on 6.4.2019.
//

#include <game/Logics.hpp>
#include <game/PhysicsComponent.hpp>
#include <Ecs.hpp>
#include <SFML/Window/Keyboard.hpp>


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
