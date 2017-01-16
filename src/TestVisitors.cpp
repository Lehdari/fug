#include "TestVisitors.hpp"

#include <cstdio> // TEMP


using namespace fug;


bool TestVisitor1::operator()(TestComponent1& component)
{
    component.a++;
    component.b--;
    printf("TestVisitor1, TestComponent1[%llu]: [%d, %d]\n", component._nodeId, component.a, component.b);
    return true;
}

bool TestVisitor2::operator()(TestComponent1& component1,
                              TestComponent2& component2)
{
    component1.a++;
    component1.b--;
    component2.a += 1.0f;
    component2.b -= 1.0f;
    printf("TestVisitor2, TestComponent1[%llu]: [%d, %d]\n", component1._nodeId, component1.a, component1.b);
    printf("TestVisitor2, TestComponent2[%llu]: [%0.2f, %0.2f]\n", component2._nodeId, component2.a, component2.b);
    return true;
}

bool TestVisitor3::operator()(TestComponent1& component1,
                              TestComponent2& component2,
                              TestComponent3& component3)
{
    component1.a++;
    component1.b--;
    component2.a += 1.0f;
    component2.b -= 1.0f;
    component3.a += 1.0;
    component3.b -= 1.0;
    printf("TestVisitor3, TestComponent1[%llu]: [%d, %d]\n", component1._nodeId, component1.a, component1.b);
    printf("TestVisitor3, TestComponent2[%llu]: [%0.2f, %0.2f]\n", component2._nodeId, component2.a, component2.b);
    printf("TestVisitor3, TestComponent3[%llu]: [%0.2f, %0.2f]\n", component3._nodeId, component3.a, component3.b);
    return true;
}
