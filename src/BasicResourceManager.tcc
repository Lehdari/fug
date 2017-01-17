template <typename T_InitInfo>
void BasicResourceManager::addResourceInfo(const RId& resourceId,
                                           const T_InitInfo& initInfo,
                                           const std::vector<RId>& initResources,
                                           const std::vector<RId>& depResources,
                                           bool isGraphicsResource)
{
    printf("addResourceInfo\n");    //  TEMP
}

template<typename T_Resource>
ResourcePointer<T_Resource> BasicResourceManager::getResource(const RId& resourceId)
{
    printf("getResource\n");    //  TEMP
}

template <typename T_Resource>
void BasicResourceManager::pointerOutOfReferences(ResourcePointer<T_Resource>& pointer)
{
    printf("pointerOutOfReferences\n");    //  TEMP
}
