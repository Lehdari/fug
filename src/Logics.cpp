//
// Created by Lehdari on 6.4.2019.
//

#include "Logics.hpp"
#include "PhysicsComponent.hpp"

#include <Ecs.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdio>


TestLogic1::TestLogic1() :
    _testValue  (0.0)
{
}

void TestLogic1::operator()(Ecs& ecs, const EntityId& eId)
{
    static int i=0;
    if (++i % 10 == 0)
        printf("TestLogic1: entity %llu testValue is %f\n", eId, _testValue);
    _testValue += 0.1;
    if (_testValue > 100.0)
        _testValue = 0.0;
}


TestLogic2::TestLogic2() :
    _testValue  (0.0)
{
}

void TestLogic2::operator()(Ecs& ecs, const EntityId& eId)
{
    static int i=0;
    if (++i % 10 == 0)
        printf("TestLogic2: entity %llu testValue is %d\n", eId, _testValue);
    _testValue++;
    if (_testValue > 500)
        _testValue = 0;
}


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
