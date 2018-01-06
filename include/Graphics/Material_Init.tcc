FUG_RESOURCE_INITINFO_INIT(Material, MaterialInitInfo_Default)
{
    // Check that keys are valid
    assertJsonValidity("MaterialInitInfo_Default", json,
                      {"type", "sampler2DUniforms", "vec3Uniforms", "floatUniforms"},
                      {});

    // Parse fields
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
    // Check dependency count
    if (depResources.size() < 1) {
        FUG_LOG(LogLevel::Error)("MaterialInitInfo_Default: no dependency resources defined\n");
        throw;
    }

    // Set shader
    _shader = FUG_RESOURCE_MANAGER.template getResource<ShaderProgram>(depResources[0]);

    // Bind sampler locations to texture resources
    for (auto i=1u; i<depResources.size(); ++i) {
        auto name = initInfo.sampler2DUniforms[i-1].c_str();
        auto loc = glGetUniformLocation(_shader->getId(), name);
        if (loc == -1)
            FUG_LOG(LogLevel::Error)("MaterialInitInfo_Default: invalid uniform name '%s'\n", name);
        else {
            ResourcePointer<Texture> t = FUG_RESOURCE_MANAGER.template getResource<Texture>(depResources[i]);
            _textures.push_back({loc, t});
        }
    }

    // Get vec3 uniform locations
    for (auto& u : initInfo.vec3Uniforms) {
        auto loc = glGetUniformLocation(_shader->getId(), u.first.c_str());
        if (loc == -1)
            FUG_LOG(LogLevel::Error)("MaterialInitInfo_Default: invalid uniform name '%s'\n", u.first.c_str());
        else
            _vec3s.push_back({loc, u.second});
    }

    // Get float uniform locations
    for (auto& u : initInfo.floatUniforms) {
        auto loc = glGetUniformLocation(_shader->getId(), u.first.c_str());
        if (loc == -1)
            FUG_LOG(LogLevel::Error)("MaterialInitInfo_Default: invalid uniform name '%s'\n", u.first.c_str());
        else
            _floats.push_back({loc, u.second});
    }
}

FUG_RESOURCE_DESTROY(Material, MaterialInitInfo_Default) {}
