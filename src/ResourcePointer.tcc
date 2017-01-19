template<typename T_Resource>
ResourcePointer<T_Resource>::ResourcePointer(void) :
    _resource(nullptr),
    _resourceId(),
    _referenceCount(nullptr)
{
    printf("Null constructor\n");
}

template<typename T_Resource>
ResourcePointer<T_Resource>::ResourcePointer(T_Resource* resource,
                                             const RId& resourceId,
                                             int64_t* referenceCount) :
    _resource(resource),
    _resourceId(resourceId),
    _referenceCount(referenceCount)
{
    printf("Proper constructor\n");
    if (_referenceCount) {
        ++*_referenceCount;
        _registerPointer(this);
    }
}

template<typename T_Resource>
ResourcePointer<T_Resource>::ResourcePointer(const ResourcePointer<T_Resource>& resourcePointer) :
    _resource(resourcePointer._resource),
    _resourceId(resourcePointer._resourceId),
    _referenceCount(resourcePointer._referenceCount)
{
    printf("Copy constructor\n");
    if (_referenceCount) {
        ++*_referenceCount;
        _registerPointer(this);
    }
}

template<typename T_Resource>
ResourcePointer<T_Resource>::ResourcePointer(ResourcePointer<T_Resource>&& resourcePointer) :
    _resource(resourcePointer._resource),
    _resourceId(resourcePointer._resourceId),
    _referenceCount(resourcePointer._referenceCount)
{
    printf("Move constructor\n");
    resourcePointer._resource = nullptr;
    resourcePointer._referenceCount = nullptr;
    if (_resource)
        _registerPointer(this);
}

template<typename T_Resource>
ResourcePointer<T_Resource>::~ResourcePointer(void) {
    printf("Destructor\n");
    if (_resource) {
        --*_referenceCount; // note: can go to negative values
        _unRegisterPointer(this);
    }
}

template<typename T_Resource>
ResourcePointer<T_Resource>& ResourcePointer<T_Resource>::operator=(const ResourcePointer<T_Resource>& resourcePointer) {
    printf("Copy assignment\n");
    if (_resource) {
        --*_referenceCount;
        _unRegisterPointer(this);
    }

    _resource = resourcePointer._resource;
    _resourceId = resourcePointer._resourceId;
    _referenceCount = resourcePointer._referenceCount;

    if (_referenceCount) {
        ++*_referenceCount;
        _registerPointer(this);
    }

    return *this;
}

template<typename T_Resource>
ResourcePointer<T_Resource>& ResourcePointer<T_Resource>::operator=(ResourcePointer<T_Resource>&& resourcePointer) {
    printf("Move assignment\n");
    if (_resource) {
        --*_referenceCount; // note: can go to negative values
        _unRegisterPointer(this);
    }

    _resource = resourcePointer._resource;
    _resourceId = resourcePointer._resourceId;
    _referenceCount = resourcePointer._referenceCount;
    _registerPointer(this);

    resourcePointer._resource = nullptr;
    resourcePointer._referenceCount = nullptr;

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
