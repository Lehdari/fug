//
// Created by Lehdari on 6.4.2019.
//

#ifndef ECSTESTGAME_LOGIC_HPP
#define ECSTESTGAME_LOGIC_HPP


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


#endif //ECSTESTGAME_LOGIC_HPP
