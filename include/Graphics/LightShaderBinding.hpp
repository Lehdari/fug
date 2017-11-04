#ifndef FUG_GRAPHICS_LIGHT_SHADER_BINDING_HPP
#define FUG_GRAPHICS_LIGHT_SHADER_BINDING_HPP

#include <GL/glew.h>
#include <Core/ResourceManager.hpp>
#include <Core/MathTypes.hpp>
#include <Graphics/ShaderProgram.hpp>

namespace fug {

    class FUG_RESOURCE(LightShaderBinding) {
    public:
        FUG_RESOURCE_INIT_DESTROY_DECL

        LightShaderBinding(void);

        const ResourcePointer<ShaderProgram>& getShaderProgPtr() const;
        const std::vector<GLint>& getSamplerLocations() const;
        const std::vector<GLint>& getParameterLocations() const;

    private:
        ResourcePointer<ShaderProgram> _shader;
        std::vector<GLint>             _samplerLocations;
        std::vector<GLint>             _parameterLocations;
    };

} // namespace fug

#endif // FUG_GRAPHICS_LIGHT_SHADER_BINDING_HPP
