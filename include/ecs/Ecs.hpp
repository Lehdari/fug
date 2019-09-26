//
// Project: fug
// File: Ecs.hpp
//
// Copyright (c) 2019 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#ifndef FUG_ECS_ECS_HPP
#define FUG_ECS_ECS_HPP


#include <utils/Types.hpp>
#include <utils/TypeId.hpp>
#include "System.hpp"

#include <vector>


namespace fug {

    class Ecs {
    public:
        Ecs();
        ~Ecs();

        /// Ecs objects are uncopyable and immovable
        Ecs(const Ecs&) = delete;
        Ecs(Ecs&&) = delete;

        Ecs& operator=(const Ecs&) = delete;
        Ecs& operator=(Ecs&&) = delete;

        /// Get ID of an entity with no components
        EntityId getEmptyEntityId();

        /// Check if an entity exists (has any components)
        bool entityExists(const EntityId& eId);

        /// Get component - component is default constructed and handle returned
        /// In case the component does not exist and a system is running,
        /// component construction is deferred and a null pointer returned.
        template <typename T_Component>
        T_Component* getComponent(const EntityId& eId);

        /// Set component
        /// In case the component does not exist and a system is running,
        /// component construction is deferred and a null pointer returned.
        template <typename T_Component>
        void setComponent(const EntityId& eId, T_Component&& component);

        /// Get singleton component
        template <typename T_Singleton>
        T_Singleton* getSingleton();

        /// Run system
        template <typename T_System, typename... T_Components>
        void runSystem(System<T_System, T_Components...>& system);

        /// Remove component
        /// In case a system is running, component removal is deferred.
        template <typename T_Component>
        void removeComponent(const EntityId& eId);

        /// Remove entity
        /// In case a system is running, entity removal is deferred.
        void removeEntity(const EntityId& eId);

    private:
        // Flag array indicating whether given component's containers are initialized
        bool    _componentInitialized[TypeId::nComponents];

        // Component and singleton containers
        void*   _components[TypeId::nComponents];
        void*   _singletons[TypeId::nSingletons];

        // Function pointers for deleting the components and singletons
        void    (*_componentDeleters[TypeId::nComponents])(void*, void*);
        void    (*_singletonDeleters[TypeId::nSingletons])(void*);

        // Container for deferred component add / remove
        void*   _componentsToAdd[TypeId::nComponents];
        void*   _componentsToRemove[TypeId::nComponents];

        // Function pointers for executing the deferred component add
        void    (Ecs::*_componentDeferredAdders[TypeId::nComponents])();
        void    (Ecs::*_componentDeferredRemovers[TypeId::nComponents])();

        // Function for initializing the component containers
        template <typename T_Component>
        inline void initializeComponent();

        // Function for extracting components from component container
        template <typename T_Component>
        inline T_Component& accessComponent(EntityId eId);

        // Functions for deferring component add / remove
        template <typename T_Component>
        inline void deferComponentAdd(const EntityId& eId, T_Component&& component);
        template <typename T_Component>
        inline void deferComponentRemove(const EntityId& eId);

        // Functions executing the deferred add / remove
        // (pointers to these are stored in *Deferred* arrays)
        template <typename T_Component>
        void addDeferredComponents();
        template <typename T_Component>
        void removeDeferredComponents();

        // Deleter functions (pointers to these are stored in *Deleters arrays)
        template <typename T_Component>
        static void deleteComponents(void* components, void* componentsToAdd);
        template <typename T_Singleton>
        static void deleteSingleton(void* singleton);

        // Bitmask indicating enabled components for an entity
        using ComponentMask = uint64_t;

        // Function for creating component masks for component combinations
        template <typename... T_Components>
        constexpr ComponentMask componentMask();

        // Container for component masks
        std::vector<ComponentMask>  _componentMasks;

        // Number of systems running
        int64_t _systemsRunning;

        // Check that the number of components fit to the bitmask
        static_assert(TypeId::nComponents <= 64,
            "Number of components does not fit to the bitmask of 64 bits.");
    };


    #include "Ecs.inl"

} //namespace fug


#endif //FUG_ECS_ECS_HPP
