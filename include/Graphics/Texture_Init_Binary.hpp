#ifndef FUG_TEXTURE_INIT_BINARY
#define FUG_TEXTURE_INIT_BINARY

#include "Core/ResourceManager.hpp"
#include "Graphics/Texture.hpp"
#include "Core/Binary.hpp"

#include <SFML/Graphics/Image.hpp>

namespace fug {
    struct TextureInitInfo_Binary {
        enum Source {
            SOURCE_BINARY_PNG
        } source;
        GLint wrapS;
        GLint wrapT;
        GLint minFiltering;
        GLint magFiltering;
    };

    FUG_RESOURCE_INIT(Texture, TextureInitInfo_Binary)
    {
        if (initResources.size() == 0) {
            textureId_ = 0;
            return;
        }

        if (initInfo.source != TextureInitInfo_Binary::SOURCE_BINARY_PNG) {
            return;
        }

        sf::Image img;

        auto buffer = FUG_RESOURCE_MANAGER.getResource<Binary>(initResources[0]);
        img.loadFromMemory(buffer->getBufferPtr(), buffer->getBufferSize());

        glGenTextures(1, &textureId_);
        glBindTexture(GL_TEXTURE_2D, textureId_);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getSize().x, img.getSize().y,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, initInfo.wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, initInfo.wrapT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, initInfo.minFiltering);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, initInfo.magFiltering);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    FUG_RESOURCE_DESTROY(Texture, TextureInitInfo_Binary)
    {
        if (textureId_ != 0)
            glDeleteTextures(1, &textureId_);
    }
}

#endif // FUG_TEXTURE_INIT_BINARY
