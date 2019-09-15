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
#include <functional>
#include <tuple>


namespace fug {

    class Ecs {
    public:
        Ecs() = default;

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
        // Typedef for component container tuple
        template <typename... T_Components>
        using ComponentStorage = std::tuple<std::vector<T_Components>...>;

        // Component container
        ComponentStorage<FUG_COMPONENT_TYPES>   _components;

        // Function for extracting components from container above
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
