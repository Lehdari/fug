#ifndef FUG_GRAPHICS_DIRECTIONAL_LIGHT_COMPONENT_HPP
#define FUG_GRAPHICS_DIRECTIONAL_LIGHT_COMPONENT_HPP

#include "Core/MathTypes.hpp"
#include "Graphics/LightShaderBinding.hpp"

namespace fug {

    struct DirectionalLightComponent {
        ResourcePointer<LightShaderBinding> shader;
        Vector3Glf direction;
        Vector3Glf intensity;
        Vector3Glf ambientInt;
    };

} // namespace fug

#endif // FUG_GRAPHICS_DIRECTIONAL_LIGHT_COMPONENT_HPP
