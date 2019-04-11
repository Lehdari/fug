//
// Created by Lehdari on 6.4.2019.
//

#ifndef ECSTESTGAME_LOGICS_HPP
#define ECSTESTGAME_LOGICS_HPP


#include "Logic.hpp"


LOGIC(TestLogic1) {
    TestLogic1();

    void operator()(Ecs& ecs, const EntityId& eId);

    double  _testValue;
};

LOGIC(TestLogic2) {
    TestLogic2();

    void operator()(Ecs& ecs, const EntityId& eId);

    int _testValue;
};

LOGIC(Logic_Ball) {
    Logic_Ball(const EntityId& paddleId);

    void operator()(Ecs& ecs, const EntityId& eId);

    EntityId    _paddleId;
    bool        _followPaddle;
};

LOGIC(Logic_Paddle) {
    void operator()(Ecs& ecs, const EntityId& eId);
};


#endif //ECSTESTGAME_LOGICS_HPP

