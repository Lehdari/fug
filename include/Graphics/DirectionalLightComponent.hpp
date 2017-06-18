#ifndef FUG_GRAPHICS_DIRECTIONALLIGHTCOMPONENT_HPP
#define FUG_GRAPHICS_DIRECTIONALLIGHTCOMPONENT_HPP

#include <Core/MathTypes.hpp>
#include <Core/ResourceManager.hpp>
#include <Graphics/ShaderProgram.hpp>

namespace fug {

    class DirectionalLightComponent {
    public:
        DirectionalLightComponent(ResourcePointer<ShaderProgram> shader,
                                  const std::vector<std::string>& samplerNames,
                                  const std::string& directionUniform, const Vector3Glf& direction,
                                  const std::string& colorUniform, const Vector3Glf& color,
                                  const std::string& directIntUniform, float directInt,
                                  const std::string& ambientIntUniform, float ambientInt);

        void bind(const Matrix4Glf& view);
        GLuint getShaderId();

    private:
        ResourcePointer<ShaderProgram> _shader;
        std::vector<GLint>             _samplerLocs;
        GLint                          _directionULoc;
        GLint                          _colorULoc;
        GLint                          _directIntULoc;
        GLint                          _ambientIntULoc;

        Vector3Glf                     _direction;
        Vector3Glf                     _color;
        float                          _directInt;
        float                          _ambientInt;
    };

} // namespace fug

#endif // FUG_GRAPHICS_DIRECTIONALLIGHTCOMPONENT_HPP
