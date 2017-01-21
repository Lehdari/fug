#include "Graphics/Texture.hpp"

using namespace fug;

Texture::Texture(void) :
    textureId_(0)
{}

void Texture::bind(GLenum target) const
{
    glBindTexture(target, textureId_);
}

