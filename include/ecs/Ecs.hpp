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

        /// Add component - component is default constructed and handle returned
        /// In case the component exists, component remains unchanged and
        /// handle to existing component is returned.
        /// In case the component does not exist and a system is running,
        /// component construction is deferred and a null pointer is returned.
        template <typename T_Component>
        T_Component* addComponent(const EntityId& eId);

        /// Get component
        /// In case the component does not exist, a null pointer is returned.
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
        // Struct for storing deferred operations
        struct DeferredOperation {
            enum Type {
                COMPONENT_ADD,
                COMPONENT_REMOVE,
                ENTITY_REMOVE
            }           type;
            union {
                void (Ecs::*componentAdd)(const EntityId&, size_t componentId);
                void (Ecs::*componentRemove)(const EntityId&);
            }           operation;
            EntityId    entityId;
            size_t      componentId; // component position in _deferredComponents vector

            // constructor for operations not requiring component storage
            DeferredOperation(
                Type type,
                EntityId entityId) :
                type        (type),
                entityId    (entityId),
                componentId (0)
            {}

            // contructor for operations requiring component storage
            template <typename T_Component>
            DeferredOperation(
                Type type,
                EntityId entityId,
                T_Component&& component,
                Ecs* ecs);
        };

        // Flag array indicating whether given component's containers are initialized
        bool    _componentInitialized[TypeId::nComponents];

        // Component and singleton containers
        void*   _components[TypeId::nComponents];
        void*   _singletons[TypeId::nSingletons];

        // Function pointers for deleting the components and singletons
        void    (*_componentDeleters[TypeId::nComponents])(void*, void*);
        void    (*_singletonDeleters[TypeId::nSingletons])(void*);

        // Containers for deferred component operations
        std::vector<DeferredOperation>  _deferredOperations;
        void*                           _deferredComponents[TypeId::nComponents];
        EntityId                        _maxDeferredEntityId;

        // Function for initializing the component containers
        template <typename T_Component>
        inline void initializeComponent();

        // Function for extracting components from component container
        template <typename T_Component>
        inline T_Component& accessComponent(EntityId eId);

        // Functions for deferring operations
        template <typename T_Component>
        inline void deferComponentAdd(const EntityId& eId, T_Component&& component);
        template <typename T_Component>
        inline void deferComponentRemove(const EntityId& eId);
        inline void deferEntityRemove(const EntityId& eId);

        // Functions executing the deferred operations
        void executeDeferredOperations();
        template <typename T_Component>
        void deferredComponentAdd(const EntityId& eId, size_t componentId);
        template <typename T_Component>
        void deferredComponentRemove(const EntityId& eId);


        // Deleter functions (pointers to these are stored in *Deleters arrays)
        template <typename T_Component>
        static void deleteComponents(void* components, void* deferredOperations);
        template <typename T_Singleton>
        static void deleteSingleton(void* singleton);

        // Bitmask indicating enabled components for an entity
        using ComponentMask = uint64_t;

        // Function for creating component masks for component combinations
        template <typename... T_Components>
        constexpr ComponentMask componentMask();

        // Container for component masks
        std::vector<ComponentMask>      _componentMasks;
        // Last bit is deserved for signifying a deferred operation on an entity
        static constexpr ComponentMask  _deferredOperationMask = 0x08000000000000000;

        // Number of systems running
        int64_t _systemsRunning;

        // Check that the number of components fit to the bitmask
        static_assert(TypeId::nComponents <= 63,
            "Number of components does not fit to the bitmask of 64 bits.");
    };


    #include "Ecs.inl"

} //namespace fug


#endif //FUG_ECS_ECS_HPP
