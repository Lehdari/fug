#ifndef FUG_TEXTURE_INIT_COLOR
#define FUG_TEXTURE_INIT_COLOR

#include "Core/ResourceManager.hpp"
#include "Graphics/Texture.hpp"

namespace fug {
    struct TextureInitInfo_Color{
        Vector4Glf color;
    };

    FUG_RESOURCE_INIT(Texture, TextureInitInfo_Color)
    {
        glGenTextures(1, &textureId_);
        glBindTexture(GL_TEXTURE_2D, textureId_);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1,
                     0, GL_RGBA, GL_FLOAT, initInfo.color.data());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        _textureSize = Vector2Glf(1, 1);
    }

    FUG_RESOURCE_DESTROY(Texture, TextureInitInfo_Color)
    {
        if (textureId_ != 0)
            glDeleteTextures(1, &textureId_);
    }
}

#endif // FUG_TEXTURE_INIT_COLOR
