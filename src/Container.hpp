//
// Created by Lehdari on 2.4.2018.
//

#ifndef CONTAINERTEST_CONTAINER_HPP
#define CONTAINERTEST_CONTAINER_HPP


#include "System.hpp"

#include <cstdint>
#include <vector>
#include <functional>
#include <tuple>


class Container {
public:
    Container();
    ~Container();

    /// Add new entity
    uint64_t addEntity();

    /// Add component for the current entity
    template <typename T>
    void addComponent(const T& component);

    /// Run system
    template <typename T_DerivedSystem, typename... Components>
    void runSystem(System<T_DerivedSystem, Components...>& system);

private:
    /// Wrapper type for components
    template <typename T>
    struct ComponentWrapper {
        uint64_t    entityId;
        T           component;

        ComponentWrapper(uint64_t& eId, const T& c) :
            entityId(eId), component(c) {}
    };

    /// TypeId system
    static uint64_t typeIdCounter;
    template <typename T>
    static uint64_t typeId();

    /// Component vector handling functions
    template <typename T>
    std::vector<ComponentWrapper<T>>& accessComponents();

    template <typename T>
    static void deleteComponents(void* components);

    template <typename T>
    using ComponentIterator = typename std::vector<ComponentWrapper<T>>::iterator;

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
template <typename T>
void Container::addComponent(const T& component)
{
    auto& v = accessComponents<T>();
    v.emplace_back(_entityId, component);
}

template<typename T_DerivedSystem, typename... Components>
void Container::runSystem(System<T_DerivedSystem, Components...>& system) {
    auto cIters = std::make_tuple(accessComponents<Components>().begin()...);
    //system(...);
    for (uint64_t eId=0; eId<=_entityId; ++eId) {
        if (increaseIterators<Components...>(eId, std::get<typename std::vector<ComponentWrapper<Components>>::iterator>(cIters)...))
            system(std::get<typename std::vector<ComponentWrapper<Components>>::iterator>(cIters)->component...);
    }
}

/// Private member functions
template <typename T>
uint64_t Container::typeId()
{
    static uint64_t tId = typeIdCounter++;
    return tId;
}

template<typename T>
std::vector<Container::ComponentWrapper<T>>& Container::accessComponents()
{
    auto tId = typeId<T>();
    if (tId == _components.size()) {
        _components.push_back(new std::vector<T>);
        _componentDeleters.push_back(std::bind(&deleteComponents<T>, _components.back()));
    }
    return *static_cast<std::vector<ComponentWrapper<T>>*>(_components[tId]);
}

template<typename T>
void Container::deleteComponents(void *components) {
    auto* v = static_cast<std::vector<ComponentWrapper<T>>*>(components);

    delete static_cast<std::vector<ComponentWrapper<T>>*>(components);
}

template<typename... T_Components>
bool Container::increaseIterators(uint64_t eId, ComponentIterator<T_Components>&... iters) {
    return (increaseIterator<T_Components>(iters, eId) && ...);
}

template<typename T_Component>
bool Container::increaseIterator(ComponentIterator<T_Component>& it, uint64_t eId) {
    while (it->entityId < eId)
        ++it;

    if (it->entityId > eId)
        return false;

    return true;
}


#endif // CONTAINERTEST_CONTAINER_HPP
