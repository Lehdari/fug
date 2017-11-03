FUG_RESOURCE_INITINFO_INIT(Material, MaterialInitInfo_Default)
{
    if (json.find("sampler2DUniforms") != json.end()) {
        for (auto& u : json["sampler2DUniforms"])
            initInfo.sampler2DUniforms.push_back(u);
    }
    if (json.find("vec3Uniforms") != json.end()) {
        for (auto it = json["vec3Uniforms"].begin(); it != json["vec3Uniforms"].end(); it++) {
            auto v = it.value();
            initInfo.vec3Uniforms.push_back({it.key(), Vector3Glf(v[0], v[1], v[2])});
        }
    }
    if (json.find("floatUniforms") != json.end()) {
        for (auto it = json["floatUniforms"].begin(); it != json["floatUniforms"].end(); it++)
            initInfo.floatUniforms.push_back({it.key(), it.value()});
    }
}

FUG_RESOURCE_INIT(Material, MaterialInitInfo_Default) {
    if (depResources.size() < 1)
        return;

    _shader = FUG_RESOURCE_MANAGER.template getResource<ShaderProgram>(depResources[0]);

    for (auto i=1u; i<depResources.size(); ++i) {
        GLint uLoc = glGetUniformLocation(_shader->getId(), initInfo.sampler2DUniforms[i-1].c_str());
        ResourcePointer<Texture> t = FUG_RESOURCE_MANAGER.template getResource<Texture>(depResources[i]);
        _textures.push_back({uLoc, t});
    }

    for (auto& u : initInfo.vec3Uniforms)
        _vec3s.push_back({glGetUniformLocation(_shader->getId(), u.first.c_str()), u.second});
    for (auto& u : initInfo.floatUniforms)
        _floats.push_back({glGetUniformLocation(_shader->getId(), u.first.c_str()), u.second});
}

FUG_RESOURCE_DESTROY(Material, MaterialInitInfo_Default) {}
