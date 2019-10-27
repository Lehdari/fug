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
T_Component* Ecs::addComponent(const EntityId& eId)
{
    constexpr auto tId = TypeId::component<T_Component>();

    // Initialize component containers
    initializeComponent<T_Component>();

    // Retrieve the pointer to component vector with the type id
    auto* v = static_cast<std::vector<T_Component>*>(_components[tId]);

    if (_systemsRunning > 0) {
        if (v->size() <= eId || _componentMasks.size() <= eId) {
            // Component needs to be added, defer it
            deferComponentAdd<T_Component>(eId, T_Component());
            return nullptr;
        }
        else {
            if ((_componentMasks[eId] & componentMask<T_Component>()) > 0) {
                // Component already exists, return it
                return &(*v)[eId];
            }
            else {
                // Entity exists but the component doesn't, defer the add
                deferComponentAdd<T_Component>(eId, T_Component());
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
T_Component* Ecs::getComponent(const EntityId& eId)
{
    constexpr auto tId = TypeId::component<T_Component>();

    // Check if the component exists
    if ((_componentMasks[eId] & componentMask<T_Component>()) > 0) {
        auto* v = static_cast<std::vector<T_Component>*>(_components[tId]);
        return &(*v)[eId];
    }

    return nullptr;
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

    // addComponent is guaranteed not to return nullptr since no systems are running
    *addComponent<T_Component>(eId) = component;
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

    // Execute deferred operations once all systems are finished
    if (_systemsRunning == 0)
        executeDeferredOperations();
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
Ecs::DeferredOperation::DeferredOperation(
    Type type,
    EntityId entityId,
    T_Component&& component,
    Ecs* ecs
    ) :
    type        (type),
    entityId    (entityId)
{
    constexpr auto tId = TypeId::component<T_Component>();
    // add component to deferred components vector
    auto* v = static_cast<std::vector<T_Component>*>(ecs->_deferredComponents[tId]);
    v->emplace_back(std::move(component));
    componentId = v->size()-1;

    if (type == COMPONENT_ADD)
        operation.componentAdd = &Ecs::deferredComponentAdd<T_Component>;
    else if (type == COMPONENT_REMOVE)
        operation.componentRemove = &Ecs::deferredComponentRemove<T_Component>;
}

template <typename T_Component>
inline void Ecs::initializeComponent()
{
    constexpr auto tId = TypeId::component<T_Component>();

    if (!_componentInitialized[tId]) {
        // allocate containers and set deleter for the component type
        _components[tId] = new std::vector<T_Component>;
        _deferredComponents[tId] = new std::vector<T_Component>;
        _componentDeleters[tId] = &deleteComponents<T_Component>;

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
    _deferredOperations.emplace_back
        (DeferredOperation::COMPONENT_ADD, eId, std::move(component), this);
}

template <typename T_Component>
inline void Ecs::deferComponentRemove(const EntityId& eId)
{
    _deferredOperations.emplace_back(DeferredOperation::COMPONENT_REMOVE, eId);
}

template <typename T_Component>
void Ecs::deferredComponentAdd(const EntityId& eId, size_t componentId)
{
    constexpr auto tId = TypeId::component<T_Component>();
    auto* v = static_cast<std::vector<T_Component>*>(_components[tId]);
    auto* dv = static_cast<std::vector<T_Component>*>(_deferredComponents[tId]);

    // Resize the component and mask vectors to the required size
    if (v->size() <= eId)
        v->resize(eId + 1);
    if (_componentMasks.size() <= eId)
        _componentMasks.resize(eId + 1);

    // Set the component
    (*v)[eId] = std::move((*dv)[componentId]);

    // Mark the component as enabled
    _componentMasks[eId] |= componentMask<T_Component>();

    // Clear the deferred component vector once the last component is processed
    if (componentId >= dv->size()-1)
        dv->clear();
}

template <typename T_Component>
void Ecs::deferredComponentRemove(const EntityId& eId)
{
    if (_componentMasks.size() <= eId)
        return;

    // Mark the component as disabled
    _componentMasks[eId] &= ~componentMask<T_Component>();
}

template <typename T_Component>
void Ecs::deleteComponents(void* components, void* deferredComponents)
{
    delete static_cast<std::vector<T_Component>*>(components);
    delete static_cast<std::vector<T_Component>*>(deferredComponents);
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
