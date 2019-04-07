//
// Created by Lehdari on 6.4.2019.
//

#include "Logics.hpp"

#include <cstdio>


TestLogic1::TestLogic1() :
    _testValue  (0.0)
{
}

void TestLogic1::operator()(Ecs& ecs, const EntityId& eId)
{
    static int i=0;
    if (++i % 10 == 0)
        printf("TestLogic1: entity %llu testValue is %f\n", eId, _testValue);
    _testValue += 0.1;
    if (_testValue > 100.0)
        _testValue = 0.0;
}


TestLogic2::TestLogic2() :
    _testValue  (0.0)
{
}

void TestLogic2::operator()(Ecs& ecs, const EntityId& eId)
{
    static int i=0;
    if (++i % 10 == 0)
        printf("TestLogic2: entity %llu testValue is %d\n", eId, _testValue);
    _testValue++;
    if (_testValue > 500)
        _testValue = 0;
}
