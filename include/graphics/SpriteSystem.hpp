//
// Project: fug
// File: SpriteSystem.hpp
//
// Copyright (c) 2021 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#ifndef FUG_GRAPHICS_SPRITESYSTEM_HPP
#define FUG_GRAPHICS_SPRITESYSTEM_HPP


#include <ecs/System.hpp>
#include <ecs/Ecs.hpp>

#include "SpriteComponent.hpp"
#include "Orientation2DComponent.hpp"


namespace fug {

    class SpriteSingleton;


    FUG_SYSTEM(SpriteSystem, SpriteComponent, Orientation2DComponent) {
    public:
        SpriteSystem(fug::Ecs& ecs);

        void operator()(const fug::EntityId& eId,
            SpriteComponent& spriteComponent, Orientation2DComponent& orientationComponent);

    private:
        SpriteSingleton*    _spriteSingleton;
    };

} // namespace fug


#endif //FUG_GRAPHICS_SPRITESYSTEM_HPP
