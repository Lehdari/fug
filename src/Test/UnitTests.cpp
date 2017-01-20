#include "Test/UnitTests.hpp"

#include <cstdio>


//#if FUG_UNIT_TEST == 1
/*
#include "Scene.hpp"
#include "TestVisitors.hpp"
#include "TestComponents.hpp"

void fug::unitTest(void) {
    EId nid[10] = {0};
    uint64_t i = 0;

    TestComponent1 tc11; tc11.a = 3; tc11.b = 4;
    //TestComponent1 tc12; tc12.a = 5; tc12.b = 6;

    //nid[i++] = FUG_SCENE.addEntity();
    nid[i++] = FUG_SCENE.addEntity(TestComponent1(), TestComponent2(), TestComponent3());
    nid[i++] = FUG_SCENE.addEntity();
    nid[i++] = FUG_SCENE.addEntity(std::move(tc11), TestComponent2(), TestComponent3());
    nid[i++] = FUG_SCENE.addEntity(TestComponent1(), TestComponent3());
    nid[i++] = FUG_SCENE.addEntity(TestComponent1(), TestComponent2());

    FUG_SCENE.print();

    TestVisitor1 visitor1;
    TestVisitor2 visitor2;
    TestVisitor3 visitor3;

    printf("Visiting with TestVisitor1:\n");
    FUG_SCENE.accept(visitor1);
    printf("Visiting with TestVisitor2:\n");
    FUG_SCENE.accept(visitor2);
    printf("Visiting with TestVisitor3:\n");
    FUG_SCENE.accept(visitor3);


    FUG_SCENE.removeEntity(nid[2]);
    FUG_SCENE.removeEntity(nid[5]);

    FUG_SCENE.print();

}
*/
//#elif FUG_UNIT_TEST == 2

#include "Core/ResourceManager.hpp"
#include "Core/ResourcePointer.hpp"
#include "Test/TestResources.hpp"
#include "Test/TestResources_Init.hpp"

void fug::unitTest(void) {

void fug::resourceTest(void) {
    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource1, TestResource1_Init_Default>
        (1, TestResource1_Init_Default());
    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource1, TestResource1_Init_Default>
        (2, TestResource1_Init_Default());
    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource1, TestResource1_Init_Default>
        (3, TestResource1_Init_Default());
    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource1, TestResource1_Init_Default>
        (4, TestResource1_Init_Default());

    printf("Null initialization:\n");
    ResourcePointer<TestResource1>   resPtr1;
    ResourcePointer<TestResource1>   resPtr2;
    ResourcePointer<TestResource1>   resPtr3;
    ResourcePointer<TestResource1>   resPtr4;
    printf("More null initialization:\n");
    //ResourcePointer<TestResource1>   resPtr5;
    //ResourcePointer<TestResource1>   resPtr6;
    //ResourcePointer<TestResource1>   resPtr7;
    //ResourcePointer<TestResource1>   resPtr8;


    printf("Proper initialization:\n");
    auto resPtr9 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(1);
    auto resPtr10 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(2);
    auto resPtr11 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(3);
    auto resPtr12 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(4);
    printf("More proper initialization\n");
    auto resPtr13 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(1);
    auto resPtr14 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(2);

    printf("Null to new:\n");
    auto resPtr17(resPtr1);
    auto resPtr18 = std::move(resPtr2);
    auto resPtr19 = resPtr3;
    auto resPtr20 = std::move(resPtr4);

    printf("Proper to new:\n");
    auto resPtr21(resPtr9);
    auto resPtr22(std::move(resPtr10));
    auto resPtr23 = resPtr11;
    auto resPtr24 = std::move(resPtr12);

    printf("Proper to proper:\n");
    resPtr21 = resPtr13;
    resPtr22 = resPtr14;
}

void fug::unitTest(void) {
    resourceTest();
}

//#endif  //  FUG_UNIT_TEST
