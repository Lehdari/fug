//
// Project: fug
// File: Ecs.inl
//
// Copyright (c) 2019 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

/// Public member functions

template <typename T_Component>
T_Component* Ecs::getComponent(const EntityId& eId)
{
    constexpr auto tId = TypeId::component<T_Component>();

    // Initialize component containers
    initializeComponent<T_Component>();

    // Retrieve the pointer to component vector with the type id
    auto* v = static_cast<std::vector<T_Component>*>(_components[tId]);

    if (_systemsRunning > 0) {
        if (v->size() <= eId || _componentMasks.size() <= eId) {
            // Component needs to be added, defer it
            deferComponentAdd(eId, T_Component());
            return nullptr;
        }
        else {
            if ((_componentMasks[eId] & componentMask<T_Component>()) > 0) {
                // Component already exists, return it
                return &(*v)[eId];
            }
            else {
                // Entity exists but the component doesn't, defer the add
                deferComponentAdd(eId, T_Component());
                return nullptr;
            }
        }
    }

    // Resize the component and mask vectors to the required size
    if (_componentMasks.size() <= eId)
        _componentMasks.resize(eId+1);
    if (v->size() <= eId)
        v->resize(eId+1);
    else if ((_componentMasks[eId] & componentMask<T_Component>()) == 0) {
        // Component is disabled, reset it (since disabling does not
        // change the contents of a component)
        (*v)[eId] = T_Component();
    }

    // Mark the component as enabled
    _componentMasks[eId] |= componentMask<T_Component>();

    return &(*v)[eId];
}

template <typename T_Component>
void Ecs::setComponent(const EntityId& eId, T_Component&& component)
{
    // Initialize component containers
    initializeComponent<T_Component>();

    // Defer the component set if a system is running
    if (_systemsRunning > 0) {
        deferComponentAdd(eId, std::move(component));
        return;
    }

    // getComponent is guaranteed not to return nullptr since no systems are running
    *getComponent<T_Component>(eId) = component;
}

template <typename T_Singleton>
T_Singleton* Ecs::getSingleton()
{
    constexpr auto tId = TypeId::singleton<T_Singleton>();
    auto* s = static_cast<T_Singleton*>(_singletons[tId]);

    // Allocate and construct the singleton if it doesn't exist yet
    if (s == nullptr) {
        _singletons[tId] = s = new T_Singleton;
        _singletonDeleters[tId] = &deleteSingleton<T_Singleton>;
    }

    return s;
}

template <typename T_DerivedSystem, typename... T_Components>
void Ecs::runSystem(System<T_DerivedSystem, T_Components...>& system)
{
    ++_systemsRunning;

    for (EntityId eId = 0; eId < _componentMasks.size(); ++eId) {
        // Check if the entity has all the required components enabled
        if ((_componentMasks[eId] & componentMask<T_Components...>()) ==
            componentMask<T_Components...>()) {
            // Call the system
            system(eId, accessComponent<T_Components>(eId)...);
        }
    }

    --_systemsRunning;

    // Perform deferred component add / remove once all systems are finished
    if (_systemsRunning == 0) {
        for (auto& cda : _componentDeferredAdders)
            if (cda) (this->*cda)();
        for (auto& cdr : _componentDeferredRemovers)
            if (cdr) (this->*cdr)();
    }
}

template <typename T_Component>
void Ecs::removeComponent(const EntityId& eId)
{
    // Initialize component containers
    initializeComponent<T_Component>();

    if (_componentMasks.size() <= eId)
        return;

    if (_systemsRunning > 0 &&
        (_componentMasks[eId] & componentMask<T_Component>()) > 0) {
        // Systems running, defer the removal
        deferComponentRemove<T_Component>(eId);
        return;
    }

    // Mark the component as disabled
    _componentMasks[eId] &= ~componentMask<T_Component>();
}


/// Private member functions

template <typename T_Component>
inline void Ecs::initializeComponent()
{
    constexpr auto tId = TypeId::component<T_Component>();

    if (!_componentInitialized[tId]) {
        _components[tId] = new std::vector<T_Component>;
        _componentDeleters[tId] = &deleteComponents<T_Component>;
        _componentsToAdd[tId] = new std::vector<std::pair<EntityId, T_Component>>;
        _componentDeferredAdders[tId] = &addDeferredComponents<T_Component>;
        _componentsToRemove[tId] = new std::vector<EntityId>;
        _componentDeferredRemovers[tId] = &removeDeferredComponents<T_Component>;

        _componentInitialized[tId] = true;
    }
}

template <typename T_Component>
inline T_Component& Ecs::accessComponent(EntityId eId)
{
    constexpr auto tId = TypeId::component<T_Component>();
    return (*static_cast<std::vector<T_Component>*>(_components[tId]))[eId];
}

template <typename T_Component>
inline void Ecs::deferComponentAdd(const EntityId& eId, T_Component&& component)
{
    constexpr auto tId = TypeId::component<T_Component>();

    // Deferred component adding requires also the entity id, hence the std::pair
    auto* v = static_cast<std::vector<std::pair<EntityId, T_Component>>*>
        (_componentsToAdd[tId]);

    v->emplace_back(eId, component);
}

template <typename T_Component>
inline void Ecs::deferComponentRemove(const EntityId& eId)
{
    constexpr auto tId = TypeId::component<T_Component>();

    auto* v = static_cast<std::vector<EntityId>*>(_componentsToRemove[tId]);

    v->emplace_back(eId);
}

template <typename T_Component>
void Ecs::addDeferredComponents()
{
    constexpr auto tId = TypeId::component<T_Component>();

    auto* cav = static_cast<std::vector<std::pair<EntityId, T_Component>>*>
        (_componentsToAdd[tId]);
    auto* v = static_cast<std::vector<T_Component>*>(_components[tId]);

    for (auto& c : *cav) {
        // Resize the component and mask vectors to the required size
        if (v->size() <= c.first)
            v->resize(c.first+1);
        if (_componentMasks.size() <= c.first)
            _componentMasks.resize(c.first+1);

        // Set the component
        (*v)[c.first] = std::move(c.second);

        // Mark the component as enabled
        _componentMasks[c.first] |= componentMask<T_Component>();
    }

    cav->clear();
}

template <typename T_Component>
void Ecs::removeDeferredComponents()
{
    constexpr auto tId = TypeId::component<T_Component>();

    auto* crv = static_cast<std::vector<EntityId>*>(_componentsToRemove[tId]);

    for (auto& eId : *crv) {
        if (_componentMasks.size() <= eId)
            continue;

        // Mark the component as disabled
        _componentMasks[eId] &= ~componentMask<T_Component>();
    }

    crv->clear();
}

template <typename T_Component>
void Ecs::deleteComponents(void* components, void* componentsToAdd)
{
    delete static_cast<std::vector<T_Component>*>(components);
    delete static_cast<std::vector<std::pair<EntityId, T_Component>>*>
        (componentsToAdd);
}

template <typename T_Singleton>
void Ecs::deleteSingleton(void* singleton)
{
    delete static_cast<T_Singleton*>(singleton);
}

template <typename... T_Components>
constexpr Ecs::ComponentMask Ecs::componentMask()
{
    // Bitmasks for components can be generated compile-time with fold expression
    return ((1 << TypeId::component<T_Components>()) | ...);
}
