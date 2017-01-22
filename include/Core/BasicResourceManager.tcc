template <typename T_Resource, typename T_InitInfo>
void BasicResourceManager::addResourceInfo(const RId& resourceId,
                                           const T_InitInfo& initInfo,
                                           const std::vector<RId>& initResources,
                                           const std::vector<RId>& depResources,
                                           bool isGraphicsResource)
{
    auto& initInfos = accessInitInfos<T_InitInfo>();

    auto capacity = initInfos.capacity();
    initInfos.push_back(initInfo);
    //  reassign all init info pointers if initInfo vector gets reallocated
    auto initInfoTypeId = getTypeId<T_InitInfo>();
    if (initInfos.size() > capacity) {
        for (auto& rInfo : _resourceInfos) {
            if (rInfo.second.initInfoTypeId == initInfoTypeId)
                rInfo.second.initInfo = &initInfos[rInfo.second.initInfoLoc];
        }
    }

    _resourceInfos.emplace(std::make_pair(resourceId, ResourceInfo {
        getTypeId<T_Resource>(),                //  resourceTypeId
        initInfoTypeId,                         //  initInfoTypeId
        &initInfos.back(),                      //  initInfo
        initInfos.size()-1,                     //  initInfoLoc
        nullptr,                                //  resource
        0,                                      //  resourceLoc
        initResources,                          //  initResources
        depResources,                           //  depResources
        &BasicResourceManager::initResource<T_Resource, T_InitInfo>,    //  init
        &BasicResourceManager::destroyResource<T_Resource, T_InitInfo>  //  destroy
    }));
}

class Binary;   //  TEMP

template<typename T_Resource>
ResourcePointer<T_Resource> BasicResourceManager::getResource(const RId& resourceId)
{
    try {
        auto& resourceInfo = _resourceInfos.at(resourceId);

        //  check if the type matches the id
        auto resourceTypeId = getTypeId<T_Resource>();
        if (resourceInfo.resourceTypeId != resourceTypeId)
            throw "BasicResourceManager: resource id does not match the given type";

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
    //  ResourcePointer pointers
    auto& resourcePointers = accessResourcePointerPointers<T_Resource>(pointer->_resourceId);

    resourcePointers.push_back(pointer);

    //printf("registerPointer, counter: %llu\n", (unsigned long long)resourcePointers.size());
}

template <typename T_Resource>
void BasicResourceManager::unRegisterPointer(ResourcePointer<T_Resource>* pointer)
{
    //  ResourcePointer pointers
    auto& resourcePointers = accessResourcePointerPointers<T_Resource>(pointer->_resourceId);

    resourcePointers.erase(std::remove(resourcePointers.begin(),
                                       resourcePointers.end(),
                                       pointer),
                           resourcePointers.end());

    //printf("unRegisterPointer, counter: %llu\n", (unsigned long long)resourcePointers.size());    //  TEMP
}


template <typename T_Resource, typename T_InitInfo>
void BasicResourceManager::initResource(ResourceInfo& resourceInfo)
{
    auto& resources = accessResources<T_Resource>();
    auto capacity = resources.capacity();

    //  add the new resource
    resources.emplace_back();
    auto& resource = resources.back();
    auto resourceTypeId = getTypeId<T_Resource>();
    auto initInfoTypeId = getTypeId<T_InitInfo>();

    //  reassign all init info pointers and resource pointer pointers
    //  if resources vector gets reallocated
    if (resources.size() > capacity) {
        for (auto& rInfo : _resourceInfos) {
            if (rInfo.second.initInfoTypeId == initInfoTypeId && rInfo.second.resource != nullptr)
                rInfo.second.resource = &resources[rInfo.second.resourceLoc];

        }

        //  ResourcePointer pointers
        for (auto& rpv : accessResourcePointerPointers<T_Resource>())
            for (auto* rp : rpv.second)
                rp->_resource = &resources[_resourceInfos[rpv.first].resourceLoc];
    }

    //  store location of the newly added resource
    resourceInfo.resource = &resource;
    resourceInfo.resourceLoc = resources.size()-1;

    resource.init(*static_cast<T_InitInfo*>(resourceInfo.initInfo),
                  resourceInfo.initResources,
                  resourceInfo.depResources);
}

template <typename T_Resource, typename T_InitInfo>
void BasicResourceManager::destroyResource(ResourceInfo& resourceInfo)
{
    if (resourceInfo.resource)
        static_cast<T_Resource*>(resourceInfo.resource)->template destroy<T_InitInfo>();
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
std::vector<ResourcePointer<T_Resource>*>&
    BasicResourceManager::accessResourcePointerPointers(const RId& resourceId)
{
    return accessResourcePointerPointers<T_Resource>()[resourceId];
}

template <typename T_Resource>
std::unordered_map<RId, std::vector<ResourcePointer<T_Resource>*>>&
    BasicResourceManager::accessResourcePointerPointers(void)
{
    static std::unordered_map<RId, std::vector<ResourcePointer<T_Resource>*>> m;
    return m;
}


template <typename T_Resource>
uint64_t BasicResourceManager::getTypeId(void)
{
    static uint64_t typeId = ++_typeId;
    return typeId;
}
