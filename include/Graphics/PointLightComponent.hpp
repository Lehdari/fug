#ifndef FUG_GRAPHICS_POINTLIGHTCOMPONENT_HPP
#define FUG_GRAPHICS_POINTLIGHTCOMPONENT_HPP

#include <Core/MathTypes.hpp>
#include <Core/ResourceManager.hpp>
#include <Graphics/ShaderProgram.hpp>

namespace fug {

    class PointLightComponent {
    public:
        PointLightComponent(ResourcePointer<ShaderProgram> shader,
                            const std::vector<std::string>& samplerNames,
                            const std::string& positionUniform, const Vector3Glf& position,
                            const std::string& colorUniform, const Vector3Glf& color,
                            const std::string& directIntUniform, float directInt,
                            const std::string& attenConstUniform, float attenConst,
                            const std::string& attenLinUniform, float attenLin,
                            const std::string& attenExpUniform, float attenExp);

        void bind(const Matrix4Glf& view);
        GLuint getShaderId();

        Vector3Glf                     _position;
        Vector3Glf                     _color;
        float                          _directInt;
        float                          _attenConst;
        float                          _attenLin;
        float                          _attenExp;

    private:
        ResourcePointer<ShaderProgram> _shader;
        std::vector<GLint>             _samplerLocs;
        GLint                          _positionULoc;
        GLint                          _colorULoc;
        GLint                          _directIntULoc;
        GLint                          _attenConstULoc;
        GLint                          _attenLinULoc;
        GLint                          _attenExpULoc;

    };

} // namespace fug

#endif // FUG_GRAPHICS_POINTLIGHTCOMPONENT_HPP
