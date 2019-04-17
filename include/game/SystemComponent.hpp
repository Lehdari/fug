//
// Created by Lehdari on 17.4.2019.
//

#ifndef ECSTESTGAME_SYSTEMCOMPONENT_HPP
#define ECSTESTGAME_SYSTEMCOMPONENT_HPP


#include <Ecs.hpp>
#include <engine/EventSystem.hpp>
#include <engine/LogicSystem.hpp>
#include <game/PhysicsSystem.hpp>
#include <game/SpriteRenderer.hpp>
#include <game/CollisionSystem.hpp>
#include <memory>


/// SystemComponent is a singleton component containing all the systems used
struct SystemComponent {
    std::unique_ptr<PhysicsSystem>      physicsSystem;
    std::unique_ptr<SpriteRenderer>     spriteRenderer;
    std::unique_ptr<CollisionSystem>    collisionSystem;
    std::unique_ptr<EventSystem>        eventSystem;
    std::unique_ptr<LogicSystem>        logicSystem;
};


DECLARE_COMPONENT_TEMPLATES(SystemComponent);


#endif //ECSTESTGAME_SYSTEMCOMPONENT_HPP
