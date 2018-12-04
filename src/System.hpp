//
// Created by Lehdari on 2.4.2018.
//

#ifndef TEMPLATEECS_SYSTEM_HPP
#define TEMPLATEECS_SYSTEM_HPP


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


#endif //TEMPLATEECS_SYSTEM_HPP
