#include "TestVisitors.hpp"


using namespace fug;


void TestVisitor1::operator()(TestComponent1& component)
{
    component.a++;
    component.b--;
    printf("TestVisitor1, TestComponent1: [%d, %d]\n", component.a, component.b);
}

void TestVisitor2::operator()(TestComponent1& component1,
                              TestComponent2& component2)
{
    component1.a--;
    component1.b++;
    component2.a += 1.0f;
    component2.b -= 1.0f;
    printf("TestVisitor2, TestComponent1: [%d, %d]\n", component1.a, component1.b);
    printf("TestVisitor2, TestComponent2: [%0.2f, %0.2f]\n", component2.a, component2.b);
}

void TestVisitor3::operator()(TestComponent1& component1,
                              TestComponent2& component2,
                              TestComponent3& component3)
{
    component1.a--;
    component1.b++;
    component2.a += 1.0f;
    component2.b -= 1.0f;
    component3.a += 1.0;
    component3.b -= 1.0;
    printf("TestVisitor3, TestComponent1: [%d, %d]\n", component1.a, component1.b);
    printf("TestVisitor3, TestComponent2: [%0.2f, %0.2f]\n", component2.a, component2.b);
    printf("TestVisitor3, TestComponent2: [%0.2f, %0.2f]\n", component3.a, component3.b);
}
