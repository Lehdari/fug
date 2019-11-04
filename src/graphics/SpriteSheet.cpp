#include "SpriteSheet.hpp"

using namespace fug;

SpriteSheet::SpriteSheet(const std::string &texturePath,
                         int32_t textureW, int32_t textureH,
                         uint32_t cellW, uint32_t cellH, float margin)
{
    load(texturePath, textureW, textureH, cellW, cellH, margin);
}

SpriteSheet::~SpriteSheet()
{
    glDeleteTextures(1, &textureID);
}

void SpriteSheet::load(const std::string &texturePath,
                       int32_t textureW, int32_t textureH,
                       uint32_t cellW, uint32_t cellH, float margin)
{
    if (textureID != 0)
        glDeleteTextures(1, &textureID);

    int textureChannels;
    uint8_t *textureData = stbi_load(texturePath.c_str(), &textureW, &textureH,
                                    &textureChannels, 0);
    // TODO: Different types, should be implemented in tex resource
    assert(textureChannels == 4);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureW, textureH, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, textureData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glGenerateMipmap(GL_TEXTURE_2D);


    glsprite_sheet_init(&sheet, textureID, textureW, textureH);
    glsprite_grid_init(&grid, cellW, cellH, margin);

    stbi_image_free(textureData);
}
