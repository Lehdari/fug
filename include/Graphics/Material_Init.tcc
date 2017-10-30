FUG_RESOURCE_INITINFO_INIT(Material, MaterialInitInfo_Default)
{
    auto c = json["specularColor"];
    initInfo.specularColor = Vector3f(c[0], c[1], c[2]);
    initInfo.specularExp = json["specularExp"];
}

FUG_RESOURCE_INIT(Material, MaterialInitInfo_Default) {
    if (depResources.size() < 1)
        return;

    _shader = FUG_RESOURCE_MANAGER.template getResource<ShaderProgram>(depResources[0]);

    for (auto i=1u; i<depResources.size(); ++i)
        _textures.push_back(FUG_RESOURCE_MANAGER.template getResource<Texture>(depResources[i]));

    _specularColor = initInfo.specularColor;
    _specularExp = initInfo.specularExp;
}

FUG_RESOURCE_DESTROY(Material, MaterialInitInfo_Default) {}
