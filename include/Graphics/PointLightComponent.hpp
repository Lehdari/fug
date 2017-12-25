#ifndef FUG_GRAPHICS_POINT_LIGHT_COMPONENT_HPP
#define FUG_GRAPHICS_POINT_LIGHT_COMPONENT_HPP

#include "Core/MathTypes.hpp"
#include "Graphics/LightShaderBinding.hpp"

namespace fug {

    struct PointLightComponent {
        ResourcePointer<LightShaderBinding> shader;
        ResourcePointer<Mesh> boundingMesh;
        Vector3Glf intensity;
        Vector3Glf attenuation; // constant, linear, exponential
    };

} // namespace fug

#endif // FUG_GRAPHICS_POINT_LIGHT_COMPONENT_HPP
