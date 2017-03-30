#ifndef FUG_TEXTURE_INIT_BINARY
#define FUG_TEXTURE_INIT_BINARY

#include "Core/ResourceManager.hpp"
#include "Graphics/Texture.hpp"
#include "Core/Binary.hpp"

#include <stb_image.h>

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

    FUG_RESOURCE_INITINFO_INIT(Texture, TextureInitInfo_Binary)
    {
        if (json["source"] == "SOURCE_BINARY_PNG") {
            initInfo.source = TextureInitInfo_Binary::SOURCE_BINARY_PNG;
        } else {
            throw;
        }
        initInfo.wrapS = fug::getGLenum(json["wrapS"]);
        initInfo.wrapT = fug::getGLenum(json["wrapT"]);
        initInfo.minFiltering = fug::getGLenum(json["minFiltering"]);
        initInfo.magFiltering = fug::getGLenum(json["magFiltering"]);
    }

    FUG_RESOURCE_INIT(Texture, TextureInitInfo_Binary)
    {
        if (initResources.size() == 0) {
            textureId_ = 0;
            return;
        }

        if (initInfo.source != TextureInitInfo_Binary::SOURCE_BINARY_PNG) {
            return;
        }

        auto buffer = FUG_RESOURCE_MANAGER.getResource<Binary>(initResources[0]);

        int32_t w, h;
        int channels;
        uint8_t* pixels = stbi_load_from_memory(reinterpret_cast<const unsigned char*>(buffer->getBufferPtr()),
                                                buffer->getBufferSize(),
                                                &w, &h, &channels, 4);

        // Flip texture vertically to OpenGL format
        auto size = w * h * 4;
        auto rowLen= w * 4;
        std::vector<uint8_t> tmpRow(rowLen);
        auto middle = h / 2 * rowLen;
        for (auto i = 0u; i < middle; i += rowLen) {
            auto backOffset = size - i - rowLen;
            std::copy(pixels + backOffset, pixels + backOffset + rowLen, tmpRow.begin());
            std::copy(pixels + i, pixels + i + rowLen, pixels + backOffset);
            std::copy(tmpRow.begin(), tmpRow.end(), pixels + i);
        }

        glGenTextures(1, &textureId_);
        glBindTexture(GL_TEXTURE_2D, textureId_);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, initInfo.wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, initInfo.wrapT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, initInfo.minFiltering);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, initInfo.magFiltering);
        glGenerateMipmap(GL_TEXTURE_2D);

        _textureSize = Vector2Glf(w, h);

        stbi_image_free(pixels);
    }

    FUG_RESOURCE_DESTROY(Texture, TextureInitInfo_Binary)
    {
        if (textureId_ != 0)
            glDeleteTextures(1, &textureId_);
    }
}

#endif // FUG_TEXTURE_INIT_BINARY
