#include "Scene.hpp"
#include "TestVisitors.hpp"
#include "TestComponents.hpp"

#include <tuple>


using namespace fug;


int main(void) {
    FUG_SCENE.addNode();
    FUG_SCENE.addNode(TestComponent1(),
                      TestComponent2(),
                      TestComponent3());

    return 0;
}
