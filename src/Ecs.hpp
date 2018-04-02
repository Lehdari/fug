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


class Ecs {
public:
    Ecs();
    Ecs(const Ecs&) = delete;
    Ecs(Ecs&&) = delete;
    ~Ecs();

    Ecs& operator=(const Ecs&) = delete;
    Ecs& operator=(Ecs&&) = delete;

    /// Add new entity
    uint64_t addEntity();

    /// Add component for the current entity
    template <typename T_Component>
    void addComponent(const T_Component& component);

    /// Run system
    template <typename T_DerivedSystem, typename... T_Components>
    void runSystem(System<T_DerivedSystem, T_Components...>& system);

private:
    /// Wrapper type for components
    template <typename T_Component>
    struct ComponentWrapper {
        uint64_t    entityId;
        T_Component component;

        ComponentWrapper(uint64_t& eId, const T_Component& c) :
            entityId(eId), component(c) {}
    };

    /// TypeId system
    static uint64_t typeIdCounter;
    template <typename T_Component>
    static uint64_t typeId();

    /// Component vector handling functions
    template <typename T_Component>
    std::vector<ComponentWrapper<T_Component>>& accessComponents();

    template <typename T_Component>
    static void deleteComponents(void* components);

    template <typename T_Component>
    using ComponentIterator = typename std::vector<ComponentWrapper<T_Component>>::iterator;

    template <typename... T_Components>
    static bool increaseIterators(uint64_t eId, ComponentIterator<T_Components>&... iters);

    template <typename T_Component>
    static bool increaseIterator(ComponentIterator<T_Component>& it, uint64_t eId);

    /// Component vector handling datatypes
    std::vector<void*>                  _components;
    std::vector<std::function<void()>>  _componentDeleters;

    /// ID of the last entity
    uint64_t                            _entityId;
};

/// Public member functions
template <typename T_Component>
void Ecs::addComponent(const T_Component& component)
{
    auto& v = accessComponents<T_Component>();
    v.emplace_back(_entityId, component);
}

template<typename T_DerivedSystem, typename... Components>
void Ecs::runSystem(System<T_DerivedSystem, Components...>& system) {
    auto cIters = std::make_tuple(accessComponents<Components>().begin()...);

    for (uint64_t eId=0; eId<=_entityId; ++eId) {
        if (increaseIterators<Components...>(eId, std::get<ComponentIterator<Components>>(cIters)...))
            system(std::get<ComponentIterator<Components>>(cIters)->component...);
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
std::vector<Ecs::ComponentWrapper<T_Component>>& Ecs::accessComponents()
{
    auto tId = typeId<T_Component>();
    if (tId == _components.size()) {
        _components.push_back(new std::vector<T_Component>);
        _componentDeleters.push_back(std::bind(&deleteComponents<T_Component>, _components.back()));
    }
    return *static_cast<std::vector<ComponentWrapper<T_Component>>*>(_components[tId]);
}

template<typename T_Component>
void Ecs::deleteComponents(void *components) {
    delete static_cast<std::vector<ComponentWrapper<T_Component>>*>(components);
}

template<typename... T_Components>
bool Ecs::increaseIterators(uint64_t eId, ComponentIterator<T_Components>&... iters) {
    return (increaseIterator<T_Components>(iters, eId) && ...);
}

template<typename T_Component>
bool Ecs::increaseIterator(ComponentIterator<T_Component>& it, uint64_t eId) {
    while (it->entityId < eId)
        ++it;

    if (it->entityId > eId)
        return false;

    return true;
}


#endif //TEMPLATEECS_ECS_HPP
