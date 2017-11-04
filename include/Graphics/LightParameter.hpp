#ifndef FUG_GRAPHICS_LIGHT_PARAMETER_HPP
#define FUG_GRAPHICS_LIGHT_PARAMETER_HPP

#include <GL/glew.h>
#include <Core/MathTypes.hpp>
#include <vector>

namespace fug {

    enum class LightParameter : size_t {
        Position = 0,
        Direction = 1,
        ConeAngle = 2,
        Intensity = 3,
        AmbientIntensity = 4,
        Attenuation = 5,
        PARAMETER_COUNT = 6
    };

    LightParameter getLightParameter(const std::string& s);
    std::vector<GLint> initLightParameterLocations();

} // namespace fug

#endif // FUG_GRAPHICS_LIGHT_PARAMETER_HPP
