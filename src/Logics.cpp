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
    printf("Hi my testValue is %f\n", _testValue);
    _testValue += 0.1;
    if (_testValue > 10.0)
        _testValue = 0.0;
}
