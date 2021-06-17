//
// Project: fug
// File: SpriteSystem.cpp
//
// Copyright (c) 2021 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#include <graphics/SpriteSystem.hpp>
#include <graphics/SpriteSingleton.hpp>


using namespace fug;


SpriteSystem::SpriteSystem(fug::Ecs& ecs) :
    _spriteSingleton    (ecs.getSingleton<SpriteSingleton>())
{
}

void SpriteSystem::operator()(const fug::EntityId& eId,
    SpriteComponent& spriteComponent, Orientation2DComponent& orientationComponent)
{
    if (spriteComponent._dirty) {
        auto& spriteSheet = _spriteSingleton->_spriteSheets[spriteComponent._spriteSheetId];
        int sw, sh;
        float uvLeft, uvRight, uvTop, uvBottom;
        spriteSheet.getDimensions(spriteComponent._spriteId, sw, sh);
        spriteSheet.getUVCoordinates(spriteComponent._spriteId, uvLeft, uvRight, uvTop, uvBottom);

        spriteComponent._positions[0] << -spriteComponent._origin(0), -spriteComponent._origin(1);
        spriteComponent._positions[1] << sw-spriteComponent._origin(0), -spriteComponent._origin(1);
        spriteComponent._positions[2] << sw-spriteComponent._origin(0), sh-spriteComponent._origin(1);
        spriteComponent._positions[3] << -spriteComponent._origin(0), sh-spriteComponent._origin(1);

        spriteComponent._texCoords[0] << uvLeft, uvTop;
        spriteComponent._texCoords[1] << uvRight, uvTop;
        spriteComponent._texCoords[2] << uvRight, uvBottom;
        spriteComponent._texCoords[3] << uvLeft, uvBottom;

        float rotSin = std::sin(spriteComponent._rotation);
        float rotCos = std::cos(spriteComponent._rotation);

        Mat2f rotMat, scaleMat, totalMat;
        rotMat << rotCos, -rotSin, rotSin, rotCos;
        scaleMat << spriteComponent._scale(0), 0.0f, 0.0f, spriteComponent._scale(1);
        totalMat = rotMat * scaleMat;

        for (auto& p : spriteComponent._positions)
            p = totalMat * p;

        spriteComponent._dirty = false;
    }

    auto& vertexPositions = _spriteSingleton->_spriteVertexPositions[spriteComponent._spriteSheetId];
    Vec2f pos = orientationComponent._orientation.block<2,1>(0,2);
    vertexPositions.emplace_back(pos + spriteComponent._positions[0]);
    vertexPositions.emplace_back(pos + spriteComponent._positions[1]);
    vertexPositions.emplace_back(pos + spriteComponent._positions[3]);
    vertexPositions.emplace_back(pos + spriteComponent._positions[3]);
    vertexPositions.emplace_back(pos + spriteComponent._positions[1]);
    vertexPositions.emplace_back(pos + spriteComponent._positions[2]);

    auto& vertexTexCoords = _spriteSingleton->_spriteVertexTexCoords[spriteComponent._spriteSheetId];
    vertexTexCoords.emplace_back(spriteComponent._texCoords[0]);
    vertexTexCoords.emplace_back(spriteComponent._texCoords[1]);
    vertexTexCoords.emplace_back(spriteComponent._texCoords[3]);
    vertexTexCoords.emplace_back(spriteComponent._texCoords[3]);
    vertexTexCoords.emplace_back(spriteComponent._texCoords[1]);
    vertexTexCoords.emplace_back(spriteComponent._texCoords[2]);
}
