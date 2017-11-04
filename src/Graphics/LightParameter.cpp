#include "Graphics/LightParameter.hpp"

#include <unordered_map>

using namespace fug;

namespace {

    const std::unordered_map<std::string, LightParameter> lightParametersByString = {
        {"Position", LightParameter::Position},
        {"Direction", LightParameter::Direction},
        {"ConeAngle", LightParameter::ConeAngle},
        {"Intensity", LightParameter::Intensity},
        {"AmbientIntensity", LightParameter::AmbientIntensity},
        {"Attenuation", LightParameter::Attenuation}
    };

    const std::vector<GLint> initialParameterLocations(static_cast<size_t>(LightParameter::PARAMETER_COUNT), -1);

}

LightParameter fug::getLightParameter(const std::string& s)
{
    return lightParametersByString.at(s);
}

std::vector<GLint> fug::initLightParameterLocations()
{
    return initialParameterLocations;
}
