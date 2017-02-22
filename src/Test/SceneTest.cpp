#include "Test/UnitTests.hpp"

#include "Core/Scene.hpp"

namespace fug {

    class TestComponent1 {
    public:
        int a;
        int b;
    };

    class TestComponent2 {
    public:
        float   a;
        float   b;
    };

    class TestComponent3 {
    public:
        double  a;
        double  b;
    };

    class TestVisitor1 : public Visitor<TestVisitor1, TestComponent1> {
    public:
        bool operator()(TestComponent1& component)
        {
            component.a++;
            component.b--;
            printf("TestVisitor1, TestComponent1: [%d, %d]\n", component.a, component.b);
            return true;
        }
    };

    class TestVisitor2 : public Visitor<TestVisitor2, TestComponent1,
    TestComponent2> {
    public:
        bool operator()(TestComponent1& component1,
                        TestComponent2& component2)
        {
            component1.a++;
            component1.b--;
            component2.a += 1.0f;
            component2.b -= 1.0f;
            printf("TestVisitor2, TestComponent1: [%d, %d]\n", component1.a, component1.b);
            printf("TestVisitor2, TestComponent2: [%0.2f, %0.2f]\n", component2.a, component2.b);
            return true;
        }
    };

    class TestVisitor3 : public Visitor<TestVisitor3, TestComponent1,
    TestComponent2,
    TestComponent3> {
    public:
        bool operator()(TestComponent1& component1,
                        TestComponent2& component2,
                        TestComponent3& component3)
        {
            component1.a++;
            component1.b--;
            component2.a += 1.0f;
            component2.b -= 1.0f;
            component3.a += 1.0;
            component3.b -= 1.0;
            printf("TestVisitor3, TestComponent1: [%d, %d]\n", component1.a, component1.b);
            printf("TestVisitor3, TestComponent2: [%0.2f, %0.2f]\n", component2.a, component2.b);
            printf("TestVisitor3, TestComponent3: [%0.2f, %0.2f]\n", component3.a, component3.b);
            return true;
        }
    };

}

FUG_UNIT_TEST(sceneTest) {
    using namespace fug;
    EId nid[10] = {0};
    uint64_t i = 0;

    TestComponent1 tc11; tc11.a = 3; tc11.b = 4;
    //TestComponent1 tc12; tc12.a = 5; tc12.b = 6;

    //nid[i++] = FUG_SCENE.addEntity();
    nid[i++] = FUG_SCENE.addEntity();
    FUG_SCENE.addComponent(TestComponent1());
    FUG_SCENE.addComponent(TestComponent2());
    FUG_SCENE.addComponent(TestComponent3());
    nid[i++] = FUG_SCENE.addEntity();
    nid[i++] = FUG_SCENE.addEntity();
    FUG_SCENE.addComponent(std::move(tc11));
    FUG_SCENE.addComponent(TestComponent2());
    FUG_SCENE.addComponent(TestComponent3());
    nid[i++] = FUG_SCENE.addEntity();
    FUG_SCENE.addComponent(TestComponent1());
    FUG_SCENE.addComponent(TestComponent3());
    nid[i++] = FUG_SCENE.addEntity();
    FUG_SCENE.addComponent(TestComponent1());
    FUG_SCENE.addComponent(TestComponent2());

    FUG_SCENE.print();

    FUG_SCENE.removeEntity(nid[2]);

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

    FUG_SCENE.print();
}


