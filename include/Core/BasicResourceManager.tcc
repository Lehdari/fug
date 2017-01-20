template <typename T_Resource, typename T_InitInfo>
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
            rInfo.second.initInfo = &initInfos[rInfo.second.initInfoLoc];
    }

    _resourceInfos.emplace(std::make_pair(resourceId, ResourceInfo{
        &initInfos.back(),                      //  initInfo
        initInfos.size()-1,                     //  initInfoLoc
        nullptr,                                //  resource
        0,                                      //  resourceLoc
        initResources,                          //  initResources
        depResources,                           //  depResources
        &accessResourcePointerPointers<T_Resource>(resourceId),     //  resourcePointers
        &BasicResourceManager::initResource<T_Resource, T_InitInfo> //  init
    }));
}

template<typename T_Resource>
ResourcePointer<T_Resource> BasicResourceManager::getResource(const RId& resourceId)
{
    try {
        auto& resourceInfo = _resourceInfos.at(resourceId);

        //  if the resource don't exist, it has to be loaded first
        if (resourceInfo.resource == nullptr)
            loadResource(resourceId, true);

        //  new resource is initialized and its position is stored in the info,
        //  time to create the resource pointer and return it
        return ResourcePointer<T_Resource>(static_cast<T_Resource*>(resourceInfo.resource),
                                           resourceId);
    }
    catch(...) {
        return ResourcePointer<T_Resource>();
    }
}


template <typename T_Resource>
void BasicResourceManager::registerPointer(ResourcePointer<T_Resource>* pointer)
{
    //  ResourceInfo
    auto& resourceInfo = _resourceInfos[pointer->_resourceId];

    //  ResourcePointer pointers
    auto& resourcePointers = *static_cast<std::vector<ResourcePointer<T_Resource>>*>
        (resourceInfo.resourcePointers);



    printf("registerPointer, counter: %lld\n");    //  TEMP
}

template <typename T_Resource>
void BasicResourceManager::unRegisterPointer(ResourcePointer<T_Resource>* pointer)
{
    printf("unRegisterPointer, counter: %lld\n");    //  TEMP
}


template <typename T_Resource, typename T_InitInfo>
void BasicResourceManager::initResource(const RId& resourceId, ResourceInfo& resourceInfo)
{
    auto& resources = accessResources<T_Resource>();
    auto capacity = resources.capacity();

    //  add the new resource
    resources.emplace_back();
    auto& resource = resources.back();

    //  reassign all init info pointers if resources vector gets reallocated
    if (resources.size() > capacity) {
        for (auto& rInfo : _resourceInfos)
            rInfo.second.resource = &resources[rInfo.second.resourceLoc];
    }

    //  store location of the newly added resource
    resourceInfo.resource = &resource;
    resourceInfo.resourceLoc = resources.size()-1;

    resource.init(*static_cast<T_InitInfo*>(resourceInfo.initInfo),
                  resourceInfo.initResources,
                  resourceInfo.depResources);
}


template <typename T_InitInfo>
std::vector<T_InitInfo>& BasicResourceManager::accessInitInfos(void)
{
    static std::vector<T_InitInfo> v;
    return v;
}

template <typename T_Resource>
std::vector<T_Resource>& BasicResourceManager::accessResources(void)
{
    static std::vector<T_Resource> v;
    return v;
}

template <typename T_Resource>
std::vector<ResourcePointer<T_Resource>*>& BasicResourceManager::accessResourcePointerPointers(const RId& resourceId) {
    static std::unordered_map<RId, std::vector<ResourcePointer<T_Resource>*>> m;
    return m[resourceId];
}
