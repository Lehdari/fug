#include "TestVisitors.hpp"


using namespace fug;


void TestVisitor1::operator()(TestComponent1& component)
{
    component.a++;
    component.b--;
}

void TestVisitor2::operator()(TestComponent1& component1, TestComponent2& component2)
{
    component1.a--;
    component1.b++;
    component2.a += 1.0f;
    component2.b -= 1.0f;
}
