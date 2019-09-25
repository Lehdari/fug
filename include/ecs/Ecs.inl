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

    // Retrieve the pointer to component vector with the type id
    auto* v = static_cast<std::vector<T_Component>*>(_components[tId]);

    // Allocate and construct the component vector if it doesn't exist yet
    if (v == nullptr) {
        _components[tId] = v = new std::vector<T_Component>;
        _componentDeleters[tId] = &deleteComponents<T_Component>;
    }

    // Resize the component and mask vectors to the required size
    if (v->size() <= eId)
        v->resize(eId+1);
    if (_componentMasks.size() <= eId)
        _componentMasks.resize(eId+1);

    // Mark the component as enabled
    _componentMasks[eId] |= componentMask<T_Component>();

    return &(*v)[eId];
}

template <typename T_Component>
void Ecs::setComponent(const EntityId& eId, T_Component&& component)
{
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
    for (EntityId eId = 0; eId < _componentMasks.size(); ++eId) {
        // Check if the entity has all the required components enabled
        if ((_componentMasks[eId] & componentMask<T_Components...>()) ==
            componentMask<T_Components...>()) {
            // Call the system
            system(eId, accessComponent<T_Components>(eId)...);
        }
    }
}

template <typename T_Component>
void Ecs::removeComponent(const EntityId& eId)
{
    if (_componentMasks.size() <= eId)
        return;

    // Just mark the component as disabled
    _componentMasks[eId] &= ~componentMask<T_Component>();
}


/// Private member functions

template <typename T_Component>
void Ecs::deleteComponents(void* componentVector)
{
    delete static_cast<std::vector<T_Component>*>(componentVector);
}

template <typename T_Singleton>
void Ecs::deleteSingleton(void* singleton)
{
    delete static_cast<T_Singleton*>(singleton);
}

template <typename T_Component>
inline T_Component& Ecs::accessComponent(EntityId eId)
{
    constexpr auto tId = TypeId::component<T_Component>();
    return (*static_cast<std::vector<T_Component>*>(_components[tId]))[eId];
}

template <typename... T_Components>
constexpr Ecs::ComponentMask Ecs::componentMask()
{
    // Bitmasks for components can be generated compile-time with fold expression
    return ((1 << TypeId::component<T_Components>()) | ...);
}
