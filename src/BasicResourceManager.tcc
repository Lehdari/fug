template <typename T_InitInfo>
void BasicResourceManager::addResourceInfo(const RId& resourceId,
                                           const T_InitInfo& initInfo,
                                           const std::vector<RId>& initResources,
                                           const std::vector<RId>& depResources,
                                           bool isGraphicsResource)
{
    printf("addResourceInfo\n");    //  TEMP

    auto& initInfos = accessInitInfos<T_InitInfo>();

    auto capacity = initInfos.capacity();
    initInfos.push_back(initInfo);
    //  reassign all init info pointers if initInfo vector gets reallocated
    if (initInfos.size() > capacity) {
        for (auto& rInfo : _resourceInfos)
            rInfo.initInfo = &initInfos[rInfo.initInfoLoc];
    }
    _resourceInfos.emplace_back(ResourceInfo{&initInfos.back(), initInfos.size()-1});
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


template <typename T_InitInfo>
std::vector<T_InitInfo>& BasicResourceManager::accessInitInfos(void)
{
    static std::vector<T_InitInfo> v;
    return v;
}
