//
// Project: fug
// File: SpriteSingleton.cpp
//
// Copyright (c) 2021 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#include <graphics/SpriteSingleton.hpp>
#include <utils/FileUtils.hpp>


using namespace fug;


SpriteSingleton::SpriteSingleton() :
    _windowWidth            (1280),
    _windowHeight           (720),
    _vertexArrayObjectId    (0),
    _positionBufferId       (0),
    _texCoordBufferId       (0)
{}

SpriteSingleton::~SpriteSingleton()
{
    if (_vertexArrayObjectId != 0)
        glDeleteVertexArrays(1, &_vertexArrayObjectId);
    if (_positionBufferId != 0)
        glDeleteBuffers(1, &_positionBufferId);
    if (_texCoordBufferId != 0)
        glDeleteBuffers(1, &_texCoordBufferId);
}

void SpriteSingleton::init()
{
    _shader.load(
        FUG_RES("shaders/VS_Sprite.glsl"),
        FUG_RES("shaders/FS_Sprite.glsl"));

    //  create and bind the VAO
    glGenVertexArrays(1, &_vertexArrayObjectId);
    glBindVertexArray(_vertexArrayObjectId);

    //  upload the vertex data to GPU and set up the vertex attribute arrays
    glGenBuffers(1, &_positionBufferId);
    glGenBuffers(1, &_texCoordBufferId);
}

SpriteSheetId SpriteSingleton::addSpriteSheetFromFile(
    const std::string& fileName, int spriteWidth, int spriteHeight)
{
    _spriteSheets.emplace_back(fileName, spriteWidth, spriteHeight);

    _spriteVertexPositions.resize(_spriteSheets.size());
    _spriteVertexTexCoords.resize(_spriteSheets.size());

    return _spriteSheets.size()-1;
}

void SpriteSingleton::setWindowSize(int windowWidth, int windowHeight)
{
    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
}

void SpriteSingleton::render()
{
    for (int i = 0; i < _spriteSheets.size(); ++i) {
        auto& vertexPositions = _spriteVertexPositions[i];
        auto& vertexTexCoords = _spriteVertexTexCoords[i];

        glBindBuffer(GL_ARRAY_BUFFER, _positionBufferId);
        glBufferData(GL_ARRAY_BUFFER,
                     vertexPositions.size() * sizeof(Vec2f),
                     vertexPositions.data(), GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0);

        glBindBuffer(GL_ARRAY_BUFFER, _texCoordBufferId);
        glBufferData(GL_ARRAY_BUFFER,
                     vertexTexCoords.size() * sizeof(Vec2f),
                     vertexTexCoords.data(), GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0);

        _shader.use();
        _shader.setUniform("windowWidth", _windowWidth);
        _shader.setUniform("windowHeight", _windowHeight);
        _spriteSheets[i]._texture.bind();
        _shader.setUniform("tex", 0);
        glDrawArrays(GL_TRIANGLES, 0, vertexPositions.size());

        vertexPositions.clear();
        vertexTexCoords.clear();
    }
}
