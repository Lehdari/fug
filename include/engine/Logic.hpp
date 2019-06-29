//
// Project: fug
// File: Logic.hpp
//
// Copyright (c) 2019 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#ifndef FUG_ENGINE_LOGIC_HPP
#define FUG_ENGINE_LOGIC_HPP


#include <Types.hpp>


#define LOGIC(LOGIC_TYPE) \
        struct LOGIC_TYPE : public Logic<LOGIC_TYPE>


class Ecs;


template <typename T_Logic>
struct Logic {
    void operator()(Ecs& ecs, const EntityId& eId, void* logic);
};

template <typename T_Logic>
void Logic<T_Logic>::operator()(Ecs& ecs, const EntityId& eId, void* logic)
{
    static_cast<T_Logic*>(logic)(ecs, eId);
}


#endif //FUG_ENGINE_LOGIC_HPP
