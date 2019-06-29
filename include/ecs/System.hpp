//
// Project: fug
// File: System.hpp
//
// Copyright (c) 2019 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#ifndef FUG_ECS_SYSTEM_HPP
#define FUG_ECS_SYSTEM_HPP


#include "Types.hpp"


/// Macro for easier and correct CRTP usage
#define TECS_SYSTEM(SYSTEM, ...) struct SYSTEM : public System<SYSTEM, __VA_ARGS__>


template <typename T_DerivedSystem, typename... Components>
struct System {
    void operator()(const EntityId& eId, Components&... components);
};

template <typename T_DerivedSystem, typename... Components>
void System<T_DerivedSystem, Components...>::operator()(const EntityId& eId, Components&... components)
{
    (*static_cast<T_DerivedSystem*>(this))(eId, components...);
}


#endif //FUG_ECS_SYSTEM_HPP
