//
// Created by Lehdari on 2.4.2018.
//

#ifndef TEMPLATEECS_ECS_HPP
#define TEMPLATEECS_ECS_HPP


#include "Types.hpp"
#include "System.hpp"

#include <vector>
#include <functional>
#include <tuple>


/// Use this in component header files
#define DECLARE_COMPONENT_TEMPLATES(COMPONENT)\
    extern template uint64_t Ecs::typeId<COMPONENT>();

/// Use this in component source files
#define DEFINE_COMPONENT_TEMPLATES(COMPONENT)\
    template uint64_t Ecs::typeId<COMPONENT>();


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

    /// Get component
    template <typename T_Component>
    T_Component* getComponent(const EntityId& eId);

    /// Remove component
    template <typename T_Component>
    void removeComponent(const EntityId& eId);

    /// Get singleton component
    template <typename T_Component>
    T_Component* getSingleton();

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

        bool isValid();
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
    static bool checkIterators(IteratorWrapper<T_Components>&... itWrappers);

    template <typename... T_Components>
    static bool increaseIterators(const EntityId& eId, IteratorWrapper<T_Components>&... itWrappers);

    /// Singleton component handling stuff
    template <typename T_Component>
    T_Component& accessSingleton();

    template <typename T_Component>
    void deleteSingleton(uint64_t cId);

    /// Entity ID handling stuff
    inline void checkEntityId(const EntityId& eId);

    /// Component vector handling data structures
    std::vector<void*>                  _components;
    std::vector<std::function<void()>>  _componentDeleters;

    /// Singleton component data structures
    std::vector<void*>                  _singletons;
    std::vector<std::function<void()>>  _singletonDeleters;

    /// Entity ID storage
    std::vector<EntityId>               _entityIds;
};


#include "Ecs.inl"


#endif //TEMPLATEECS_ECS_HPP
