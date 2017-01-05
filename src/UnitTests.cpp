#include "UnitTests.hpp"
#include "Scene.hpp"
#include "TestVisitors.hpp"
#include "TestComponents.hpp"





void fug::unitTest1(void) {
    auto id1 = FUG_SCENE.addNode(               TestComponent1(), TestComponent2());
    auto id2 = FUG_SCENE.addNode(               TestComponent1());
    auto id3 = FUG_SCENE.addNode(               TestComponent2());
    auto id4 = FUG_SCENE.addNode(               TestComponent1(), TestComponent2(), TestComponent3());
    auto id5 = FUG_SCENE.addNode(               TestComponent1(), TestComponent3());
    auto id6 = FUG_SCENE.addChildNode(  id2);
    auto id7 = FUG_SCENE.addChildNode(  id2,    TestComponent1());
    auto id8 = FUG_SCENE.addChildNode(  id2,    TestComponent1());
    auto id9 = FUG_SCENE.addChildNode(  id7,    TestComponent1());
    auto id10 = FUG_SCENE.addChildNode( id4);
    auto id11 = FUG_SCENE.addChildNode( id10,   TestComponent1(), TestComponent2());
    auto id12 = FUG_SCENE.addChildNode( id11,   TestComponent1(), TestComponent2(), TestComponent3());

    FUG_SCENE.print();

/*
    FUG_SCENE.addNode(TestComponent1(), TestComponent2(), TestComponent3());
    FUG_SCENE.addNode(TestComponent1(), TestComponent3());
    FUG_SCENE.addNode(TestComponent2());
    FUG_SCENE.addNode(TestComponent1());
    FUG_SCENE.addNode(TestComponent1(), TestComponent2(), TestComponent3());

    FUG_SCENE.print();
*/
    TestVisitor1 visitor1;
    TestVisitor2 visitor2;
    TestVisitor3 visitor3;

    printf("Visiting with TestVisitor1:\n");
    FUG_SCENE.accept(visitor1);
    printf("Visiting with TestVisitor2:\n");
    FUG_SCENE.accept(visitor2);
    printf("Visiting with TestVisitor3:\n");
    FUG_SCENE.accept(visitor3);

}
