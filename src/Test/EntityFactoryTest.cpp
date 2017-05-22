#include "Test/UnitTests.hpp"

#include "Engine/EntityFactory.hpp"
#include "Core/Log.hpp"

#include <iostream>


using namespace fug;


struct TestComponent1 {
    float a;
    float b;
};

FUG_COMPONENT_INIT(TestComponent1)
{
    FUG_LOG(LogLevel::Debug)("Initializing TestComponent1 from JSON\n");
    std::string str = json["a"];
    component.a = std::stof(str);
    str = json["b"];
    component.b = std::stof(str);
    FUG_LOG(LogLevel::Debug)("a: %0.2f, b: %0.2f\n", component.a, component.b);
}

struct TestComponent2 {
    float a;
    float b;
    float c;
};

FUG_COMPONENT_INIT(TestComponent2)
{
    FUG_LOG(LogLevel::Debug)("Initializing TestComponent2 from JSON\n");
    std::string str = json["a"];
    component.a = std::stof(str);
    str = json["b"];
    component.b = std::stof(str);
    str = json["c"];
    component.c = std::stof(str);
    FUG_LOG(LogLevel::Debug)("a: %0.2f, b: %0.2f, c: %0.2f\n",
        component.a, component.b, component.c);
}

FUG_VISITOR(TestVisitor, TestComponent1, TestComponent2) {
public:
    void operator()(TestComponent1& component1, TestComponent2& component2) {
        FUG_LOG(LogLevel::Debug)("%0.2f %0.2f %0.2f %0.2f %0.2f\n",
        component1.a, component1.b, component2.a, component2.b, component2.c);
    }
};

FUG_UNIT_TEST(entityFactoryTest) {
    EntityFactory entityFactory("entities.stfu");
    entityFactory.load();

    entityFactory.addEntity(std::string("TestEntity1"));
    entityFactory.addEntity(std::string("TestEntity2"));

    TestVisitor visitor;

    FUG_SCENE.accept(visitor);
}
