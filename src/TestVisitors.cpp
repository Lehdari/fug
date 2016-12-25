#include "TestVisitors.hpp"


using namespace fug;


void TestVisitor1::operator()(TestComponent1& component)
{
    component.a += 1.0f;
    component.b += 1.0f;
}
