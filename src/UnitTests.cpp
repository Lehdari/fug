#include "UnitTests.hpp"

#include <cstdio>


#if FUG_UNIT_TEST == 1

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

#elif FUG_UNIT_TEST == 2

#include "ResourceManager.hpp"
#include "ResourcePointer.hpp"
#include "TestResources.hpp"
#include "TestResources_Init.hpp"

void fug::unitTest(void) {

    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource1, TestResource1_Init_Default>(1, TestResource1_Init_Default());
    auto resPtr1 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(1);
    resPtr1->a++;
    auto resPtr2(resPtr1);
    auto resPtr3 = resPtr2;
    resPtr2 = resPtr3;
    auto resPtr4(std::move(resPtr2));
    resPtr1 = std::move(resPtr3);
}

#endif  //  FUG_UNIT_TEST
