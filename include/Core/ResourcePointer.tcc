template<typename T_Resource>
ResourcePointer<T_Resource>::ResourcePointer(void) :
    _resource(nullptr),
    _resourceId()
{
}

template<typename T_Resource>
ResourcePointer<T_Resource>::ResourcePointer(T_Resource* resource,
                                             const RId& resourceId) :
    _resource(resource),
    _resourceId(resourceId)
{
    if (_resource)
        _registerPointer(this);
}

template<typename T_Resource>
ResourcePointer<T_Resource>::ResourcePointer(const ResourcePointer<T_Resource>& resourcePointer) :
    _resource(resourcePointer._resource),
    _resourceId(resourcePointer._resourceId)
{
    if (_resource)
        _registerPointer(this);
}

template<typename T_Resource>
ResourcePointer<T_Resource>::ResourcePointer(ResourcePointer<T_Resource>&& resourcePointer) :
    _resource(resourcePointer._resource),
    _resourceId(resourcePointer._resourceId)
{
    resourcePointer._resource = nullptr;
    if (_resource)
        _registerPointer(this);
}

template<typename T_Resource>
ResourcePointer<T_Resource>::~ResourcePointer(void) {
    if (_resource)
        _unRegisterPointer(this);
}

template<typename T_Resource>
ResourcePointer<T_Resource>& ResourcePointer<T_Resource>::operator=(const ResourcePointer<T_Resource>& resourcePointer) {
    if (_resource)
        _unRegisterPointer(this);

    _resource = resourcePointer._resource;
    _resourceId = resourcePointer._resourceId;

    if (_resource)
        _registerPointer(this);

    return *this;
}

template<typename T_Resource>
ResourcePointer<T_Resource>& ResourcePointer<T_Resource>::operator=(ResourcePointer<T_Resource>&& resourcePointer) {
    if (_resource)
        _unRegisterPointer(this);

    _resource = resourcePointer._resource;
    _resourceId = resourcePointer._resourceId;

    if (_resource)
        _registerPointer(this);

    resourcePointer._resource = nullptr;

    return *this;
}

template<typename T_Resource>
T_Resource& ResourcePointer<T_Resource>::operator*(void) {
    return *_resource;
}

template<typename T_Resource>
const T_Resource& ResourcePointer<T_Resource>::operator*(void) const {
    return *_resource;
}

template<typename T_Resource>
T_Resource* ResourcePointer<T_Resource>::operator->(void) {
    return _resource;
}

template<typename T_Resource>
const T_Resource* ResourcePointer<T_Resource>::operator->(void) const {
    return _resource;
}

template<typename T_Resource>
T_Resource* ResourcePointer<T_Resource>::get(void) {
    return _resource;
}

template<typename T_Resource>
const RId& ResourcePointer<T_Resource>::getId(void) const {
    return _resourceId;
}
