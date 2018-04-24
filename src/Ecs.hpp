//
// Created by Lehdari on 2.4.2018.
//

#ifndef TEMPLATEECS_ECS_HPP
#define TEMPLATEECS_ECS_HPP


#include "System.hpp"

#include <cstdint>
#include <vector>
#include <functional>
#include <tuple>


using EntityId = uint64_t;


class Ecs {
public:
    Ecs();
    Ecs(const Ecs&) = delete;
    Ecs(Ecs&&) = delete;
    ~Ecs();

    Ecs& operator=(const Ecs&) = delete;
    Ecs& operator=(Ecs&&) = delete;

    /// Add component
    template <typename T_Component>
    void addComponent(const EntityId& eId, const T_Component& component);

    /// Remove component
    template <typename T_Component>
    void removeComponent(const EntityId& eId);

    /// Run system
    template <typename T_DerivedSystem, typename... T_Components>
    void runSystem(System<T_DerivedSystem, T_Components...>& system);

private:
    /// Wrapper type for components
    template <typename T_Component>
    struct ComponentWrapper {
        EntityId    eId;
        T_Component component;

        ComponentWrapper(const EntityId& eId, const T_Component& c = T_Component()) :
            eId(eId), component(c) {}
    };

    /// TypeId system
    static uint64_t typeIdCounter;
    template <typename T_Component>
    static uint64_t typeId();

    /// Component vector handling stuff
    template <typename T_Component>
    using ComponentVector = typename std::vector<ComponentWrapper<T_Component>>;

    template <typename T_Component>
    using ComponentIterator = typename ComponentVector<T_Component>::iterator;

    template <typename T_Component>
    struct IteratorWrapper {
        ComponentIterator<T_Component> it;
        ComponentIterator<T_Component> end;

        IteratorWrapper(const ComponentIterator<T_Component>& it,
                        const ComponentIterator<T_Component>& end) :
            it(it), end(end)
        {}

        bool increase(const EntityId& eId);
    };

    template <typename T_Component>
    ComponentVector<T_Component>& accessComponents();

    template <typename T_Component>
    bool findComponent(ComponentVector<T_Component>& cVector,
                       ComponentIterator<T_Component>& it,
                       const EntityId& eId);

    template <typename T_Component>
    void deleteComponents(uint64_t cVectorId);

    template <typename... T_Components>
    static bool increaseIterators(const EntityId& eId, IteratorWrapper<T_Components>&... itWrappers);

    /// Entity ID handling stuff
    inline void checkEntityId(const EntityId& eId);

    /// Component vector handling data structures
    std::vector<void*>                  _components;
    std::vector<std::function<void()>>  _componentDeleters;

    /// Entity ID storage
    std::vector<EntityId>               _entityIds;
};

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
void Ecs::removeComponent(const EntityId& eId)
{
    auto& v = accessComponents<T_Component>();
    ComponentIterator<T_Component> it;
    if (findComponent(v, it, eId))
        v.erase(it);
}

template <typename T_DerivedSystem, typename... T_Components>
void Ecs::runSystem(System<T_DerivedSystem, T_Components...>& system)
{
    auto cIters = std::make_tuple(
        IteratorWrapper<T_Components>(accessComponents<T_Components>().begin(),
                                      accessComponents<T_Components>().end())...);

    for (auto eId : _entityIds) {
        if (increaseIterators<T_Components...>(eId, std::get<IteratorWrapper<T_Components>>(cIters)...))
            system(std::get<IteratorWrapper<T_Components>>(cIters).it->component...);
    }
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
    if (tId == _components.size()) {
        _components.push_back(new std::vector<T_Component>);
        _componentDeleters.push_back(
            std::bind(&Ecs::deleteComponents<T_Component>,
                this, (uint64_t)_components.size()-1));
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
}

template<typename T_Component>
bool Ecs::IteratorWrapper<T_Component>::increase(const EntityId& eId)
{
    while (it != end && it->eId < eId)
        ++it;

    return (it->eId > eId || it == end) ? false : true;
}

template<typename... T_Components>
bool Ecs::increaseIterators(const EntityId& eId, IteratorWrapper<T_Components>&... itWrappers)
{
    return (itWrappers.increase(eId) && ...);
}

void Ecs::checkEntityId(const EntityId& eId)
{
    //  TODO implement binary tree search instead of linear one
    auto it = _entityIds.begin();
    for (; it != _entityIds.end() && *it < eId; ++it);
    if (it == _entityIds.end() || *it > eId)
        it = _entityIds.emplace(it, eId);
}


#endif //TEMPLATEECS_ECS_HPP
