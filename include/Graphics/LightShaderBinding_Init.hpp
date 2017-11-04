#ifndef FUG_GRAPHICS_LIGHT_SHADER_BINDING_INIT_HPP
#define FUG_GRAPHICS_LIGHT_SHADER_BINDING_INIT_HPP

#include <Core/ResourceManager.hpp>
#include <Graphics/LightShaderBinding.hpp>
#include <Graphics/LightParameter.hpp>

#include <string>
#include <tuple>
#include <vector>

namespace fug {

    /// Initialization info struct
    struct LightShaderBindingInitInfo {
        std::vector<std::string> sampler2DUniforms;
        std::vector<std::pair<std::string, std::string>> parameterUniforms;
    };

    FUG_RESOURCE_INITINFO_INIT(LightShaderBinding, LightShaderBindingInitInfo)
    {
        if (json.find("sampler2DUniforms") != json.end()) {
            for (auto& u : json["sampler2DUniforms"])
                initInfo.sampler2DUniforms.push_back(u);
        }
        if (json.find("parameterUniforms") != json.end()) {
            for (auto it = json["parameterUniforms"].begin(); it != json["parameterUniforms"].end(); it++)
                initInfo.parameterUniforms.push_back({it.key(), it.value().get<std::string>()});
        }
    }

    FUG_RESOURCE_INIT(LightShaderBinding, LightShaderBindingInitInfo) {
        if (depResources.size() < 1)
            return;

        _shader = FUG_RESOURCE_MANAGER.getResource<ShaderProgram>(depResources[0]);

        for (auto& u : initInfo.sampler2DUniforms)
            _samplerLocations.push_back(glGetUniformLocation(_shader->getId(), u.c_str()));
        _parameterLocations = initLightParameterLocations();
        for (auto& p : initInfo.parameterUniforms) {
                _parameterLocations[static_cast<size_t>(getLightParameter(p.first))] =
                    glGetUniformLocation(_shader->getId(), p.second.c_str());
        }
    }

    FUG_RESOURCE_DESTROY(LightShaderBinding, LightShaderBindingInitInfo) {}

} // namespace fug

#endif // FUG_GRAPHICS_LIGHT_SHADER_BINDING_INIT_HPP
