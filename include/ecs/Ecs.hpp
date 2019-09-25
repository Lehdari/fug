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
        template <typename T_Component>
        T_Component* getComponent(const EntityId& eId);

        /// Set component
        template <typename T_Component>
        void setComponent(const EntityId& eId, T_Component&& component);

        /// Get singleton component
        template <typename T_Singleton>
        T_Singleton* getSingleton();

        /// Run system
        template <typename T_System, typename... T_Components>
        void runSystem(System<T_System, T_Components...>& system);

        /// Remove component
        template <typename T_Component>
        void removeComponent(const EntityId& eId);

        /// Remove entity
        void removeEntity(const EntityId& eId);

    private:
        // Component and singleton containers
        void*   _components[TypeId::nComponents];
        void*   _singletons[TypeId::nSingletons];

        // Function pointers for deleting the components and singletons
        void    (*_componentDeleters[TypeId::nComponents])(void*);
        void    (*_singletonDeleters[TypeId::nSingletons])(void*);

        // Deleter functions (pointers to these are stored in *Deleters arrays)
        template <typename T_Component>
        static void deleteComponents(void* componentVector);
        template <typename T_Singleton>
        static void deleteSingleton(void* singleton);

        // Function for extracting components from component container above
        template <typename T_Component>
        inline T_Component& accessComponent(EntityId eId);

        // Bitmask indicating enabled components for an entity
        using ComponentMask = uint64_t;

        // Function for creating component masks for component combinations
        template <typename... T_Components>
        constexpr ComponentMask componentMask();

        // Container for component masks
        std::vector<ComponentMask>  _componentMasks;

        // Check that the number of components fit to the bitmask
        static_assert(TypeId::nComponents <= 64,
            "Number of components does not fit to the bitmask of 64 bits.");
    };


    #include "Ecs.inl"

} //namespace fug


#endif //FUG_ECS_ECS_HPP
