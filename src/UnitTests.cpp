#include "UnitTests.hpp"
#include "Scene.hpp"
#include "TestVisitors.hpp"
#include "TestComponents.hpp"

#include <random>


void fug::unitTest1(void) {
    std::default_random_engine r(956137926);

    //for (auto )

    auto id1 = FUG_SCENE.addNode();
    auto id2 = FUG_SCENE.addNode(TestComponent1(),
                                 TestComponent2(),
                                 TestComponent3());
    auto id3 = FUG_SCENE.addNode(TestComponent1());
    auto id4 = FUG_SCENE.addNode(TestComponent2());
    auto id5 = FUG_SCENE.addNode(TestComponent3());
    auto id6 = FUG_SCENE.addChildNode(id2);
    auto id7 = FUG_SCENE.addChildNode(id2);
    auto id8 = FUG_SCENE.addChildNode(id2);
    auto id9 = FUG_SCENE.addChildNode(id7);
    auto id10 = FUG_SCENE.addChildNode(id4);
}
