template <typename T_Implementation>
ResourceManagerBase<T_Implementation>& ResourceManagerBase<T_Implementation>::instance(void)
{
    static T_Implementation resourceManager;
    return resourceManager;
}

template <typename T_Implementation>
template <typename T_Resource, typename T_InitInfo>
void ResourceManagerBase<T_Implementation>::addResourceInfo(const RId& resourceId,
                                                            const T_InitInfo& initInfo,
                                                            const std::vector<RId>& initResources,
                                                            const std::vector<RId>& depResources,
                                                            bool isGraphicsResource)
{
    static_cast<T_Implementation*>(this)->
        addResourceInfo<T_Resource, T_InitInfo>(resourceId, initInfo,
                                                initResources, depResources,
                                                isGraphicsResource);
}

template <typename T_Implementation>
template<typename T_Resource>
ResourcePointer<T_Resource> ResourceManagerBase<T_Implementation>::getResource(const RId& resourceId)
{
    return static_cast<T_Implementation*>(this)->getResource<T_Resource>(resourceId);
}

template <typename T_Implementation>
void ResourceManagerBase<T_Implementation>::loadResource(const RId& resourceId, bool waitForFinish)
{
    static_cast<T_Implementation*>(this)->loadResource(resourceId);
}

template <typename T_Implementation>
template <typename T_Resource>
void ResourceManagerBase<T_Implementation>::pointerOutOfReferences(ResourcePointer<T_Resource>& pointer)
{
    static_cast<T_Implementation*>(this)->pointerOutOfReferences(pointer);
}
