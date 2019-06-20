//
// Created by Lehdari on 17.4.2019.
//

/// Public member functions
template <typename T_Component>
void Ecs::addComponent(const EntityId& eId, const T_Component& component)
{
    checkEntityId(eId);
    auto& v = accessComponents<T_Component>();
    ComponentIterator<T_Component> it;
    if (findComponent(v, it, eId))
        return;
    else
        v.emplace(it, eId, component);
}

template<typename T_Component>
T_Component* Ecs::getComponent(const EntityId& eId)
{
    auto& v = accessComponents<T_Component>();
    ComponentIterator<T_Component> it;
    if (findComponent(v, it, eId))
        return &(it->component);
    else
        return nullptr;
}

template<typename T_Component>
void Ecs::removeComponent(const EntityId& eId)
{
    // make sure that _componentsToRemove is up to date the first time the function is called
    static auto& v = accessComponents<T_Component>();

    auto& vr = *static_cast<std::vector<EntityId>*>(
        _componentsToRemove.at(typeId<T_Component>()));
    vr.push_back(eId);
}

template<typename T_Component>
T_Component* Ecs::getSingleton()
{
    return &accessSingleton<T_Component>();
}

template <typename T_DerivedSystem, typename... T_Components>
void Ecs::runSystem(System<T_DerivedSystem, T_Components...>& system)
{
    auto cIters = std::make_tuple(
        IteratorWrapper<T_Components>(accessComponents<T_Components>().begin(),
            accessComponents<T_Components>().end())...);

    if (!checkIterators(std::get<IteratorWrapper<T_Components>>(cIters)...))
        return;

    for (auto eId : _entityIds) {
        if (increaseIterators<T_Components...>(eId, std::get<IteratorWrapper<T_Components>>(cIters)...))
        system(eId, std::get<IteratorWrapper<T_Components>>(cIters).it->component...);
    }

    (removeComponents<T_Components>(),...);
}

/// Private member functions
template <typename T_Component>
uint64_t Ecs::typeId()
{
    static uint64_t tId = typeIdCounter++;
    return tId;
}

template<typename T_Component>
Ecs::ComponentVector<T_Component>& Ecs::accessComponents()
{
    auto tId = typeId<T_Component>();
    if (_components.size() <= tId) {
        _components.resize(tId+1, nullptr);
        _componentsToRemove.resize(tId+1, nullptr);
    }

    if (_components[tId] == nullptr) {
        _components[tId] = new ComponentVector<T_Component>;
        _componentsToRemove[tId] = new std::vector<EntityId>;
        _componentDeleters.push_back(
            std::bind(&Ecs::deleteComponents<T_Component>, this, (uint64_t)tId));
    }

    return *static_cast<ComponentVector<T_Component>*>(_components[tId]);
}

template<typename T_Component>
bool Ecs::findComponent(Ecs::ComponentVector<T_Component>& cVector,
                        ComponentIterator<T_Component>& it,
                        const EntityId& eId)
{
    //  TODO implement binary tree search instead of linear one
    it = cVector.begin();
    for (; it != cVector.end() && it->eId < eId; ++it);
    if (it == cVector.end() || it->eId > eId)
        return false;
    return true;
}

template<typename T_Component>
void Ecs::deleteComponents(uint64_t cVectorId) {
    delete static_cast<ComponentVector<T_Component>*>(_components.at(cVectorId));
    delete static_cast<std::vector<EntityId>*>(_componentsToRemove.at(cVectorId));
}

template <typename T_Component>
void Ecs::removeComponents()
{
    auto& vr = *static_cast<std::vector<EntityId>*>(
        _componentsToRemove.at(typeId<T_Component>()));

    for (auto& eId : vr) {
        auto& v = accessComponents<T_Component>();
        ComponentIterator<T_Component> it;
        if (findComponent(v, it, eId)) {
            v.erase(it);
        }
    }

    vr.clear();
}

template<typename T_Component>
bool Ecs::IteratorWrapper<T_Component>::isValid()
{
    return it != end;
}

template<typename T_Component>
bool Ecs::IteratorWrapper<T_Component>::increase(const EntityId& eId)
{
    while (it != end && it->eId < eId)
        ++it;

    return (it == end || it->eId > eId) ? false : true;
}

template<typename... T_Components>
bool Ecs::checkIterators(IteratorWrapper<T_Components>&... itWrappers)
{
    return (itWrappers.isValid() && ...);
}

template<typename... T_Components>
bool Ecs::increaseIterators(const EntityId& eId, IteratorWrapper<T_Components>&... itWrappers)
{
    return (itWrappers.increase(eId) && ...);
}

template<typename T_Component>
T_Component& Ecs::accessSingleton()
{
    auto tId = typeId<T_Component>();
    if (_singletons.size() <= tId)
        _singletons.resize(tId+1, nullptr);

    if (_singletons[tId] == nullptr) {
        _singletons[tId] = new T_Component;
        _singletonDeleters.push_back(
            std::bind(&Ecs::deleteSingleton<T_Component>, this, (uint64_t)tId));
    }
    return *static_cast<T_Component*>(_singletons[tId]);

}

template <typename T_Component>
void Ecs::deleteSingleton(uint64_t cId)
{
    delete static_cast<T_Component*>(_singletons.at(cId));
}

void Ecs::checkEntityId(const EntityId& eId)
{
    //  TODO implement binary tree search instead of linear one
    auto it = _entityIds.begin();
    for (; it != _entityIds.end() && *it < eId; ++it);
    if (it == _entityIds.end() || *it > eId)
        it = _entityIds.emplace(it, eId);
}
