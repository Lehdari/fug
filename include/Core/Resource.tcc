template<typename T_Resource>
template<typename T_ResourceInitInfo>
void Resource<T_Resource>::init(T_ResourceInitInfo initInfo,
                                std::vector<RId> initResources,
                                std::vector<RId> depResources)
{
    //if (status() != STATUS_UNINITIALIZED)
    //    return;
    //setStatus(STATUS_INITIALIZING);
    static_cast<T_Resource*>(this)->init(initInfo, initResources, depResources);
    //setStatus(STATUS_READY);
}

template<typename T_Resource>
template<typename T_ResourceInitInfo>
void Resource<T_Resource>::destroy(void) {
    //if (status() != STATUS_READY)
    //    return;
    //setStatus(STATUS_DESTROYING);
    static_cast<T_Resource*>(this)->template destroy<T_ResourceInitInfo>();
    //setStatus(STATUS_DESTROYED);
}
