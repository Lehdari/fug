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
    auto& v = std::get<std::vector<T_Component>>(_components);

    // Resize the component and mask vectors to the required size
    if (v.size() <= eId)
        v.resize(eId+1);
    if (_componentMasks.size() <= eId)
        _componentMasks.resize(eId+1);

    // Mark the component as enabled
    _componentMasks[eId] |= componentMask<T_Component>();

    return &v[eId];
}

template <typename T_Component>
void Ecs::setComponent(const EntityId& eId, T_Component&& component)
{
    *getComponent<T_Component>(eId) = component;
}

template <typename T_Singleton>
T_Singleton* Ecs::getSingleton()
{
    auto* p = std::get<std::unique_ptr<T_Singleton>>(_singletons).get();

    // Allocate and construct the singleton if it doesn't exist yet
    if (p == nullptr) {
        std::get<std::unique_ptr<T_Singleton>>(_singletons).reset(new T_Singleton);
        p = std::get<std::unique_ptr<T_Singleton>>(_singletons).get();
    }

    return p;
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
inline T_Component& Ecs::accessComponent(EntityId eId)
{
    return std::get<std::vector<T_Component>>(_components)[eId];
}

template <typename... T_Components>
constexpr Ecs::ComponentMask Ecs::componentMask()
{
    // Bitmasks for components can be generated compile-time with fold expression
    return ((1 << TypeId::component<T_Components>()) | ...);
}
