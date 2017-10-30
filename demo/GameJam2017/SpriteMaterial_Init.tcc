FUG_RESOURCE_INIT(SpriteMaterial, SpriteMaterialInitInfo_Default) {
    if (depResources.size() < 1)
        return;

    _shader = FUG_RESOURCE_MANAGER.template getResource<ShaderProgram>(depResources[0]);

    for (auto i=1u; i<depResources.size(); ++i)
        _textures.push_back(FUG_RESOURCE_MANAGER.template getResource<Texture>(depResources[i]));

    //  fetch uniform locations
    for (auto& name : initInfo.uniformSampler2DNames)
        _uniformLocations_Sampler2D.emplace_back(glGetUniformLocation(_shader->getId(), name.c_str()));
    for (auto& name : initInfo.uniformMat4Names)
        _uniformLocations_Mat4.emplace_back(glGetUniformLocation(_shader->getId(), name.c_str()));
    for (auto& name : initInfo.uniformFloatNames)
        _uniformLocations_Float.emplace_back(glGetUniformLocation(_shader->getId(), name.c_str()));
    for (auto& name : initInfo.uniformGLintNames)
        _uniformLocations_Int.emplace_back(glGetUniformLocation(_shader->getId(), name.c_str()));
    
    const Vector2Glf textureSize = _textures[0]->getSize();
    
    _spriteW = initInfo.spriteW / textureSize[0];
    _spriteH = initInfo.spriteH / textureSize[1];
    
}

FUG_RESOURCE_DESTROY(SpriteMaterial, SpriteMaterialInitInfo_Default) {}
