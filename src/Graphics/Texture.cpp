#include "Graphics/Texture.hpp"

using namespace fug;

Texture::Texture(void) :
    textureId_(0)
{}

const Vector2Glf& Texture::getSize() const
{
    return _textureSize;
}

void Texture::bind(GLenum target) const
{
    glBindTexture(target, textureId_);
}

