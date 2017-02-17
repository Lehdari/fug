#include "Test/UnitTests.hpp"

#include "Engine/ResourceLoader.hpp"
#include "Core/ResourceManager.hpp"
#include "Core/Binary.hpp"

#include <iostream>


using namespace fug;


FUG_UNIT_TEST(resourceLoaderTest) {
    std::cout << "Testing ResourceLoader\n\n";

    ResourceLoader resourceLoader("resources.stfu");
    resourceLoader.load();
    auto vertResPtr = FUG_RESOURCE_MANAGER.getResource<Binary>
        (FUG_RESOURCE_ID_MAP.getId("binary_shader_default_vert"));
    // TODO
    //printf("%s\n", vertResPtr->getBufferPtr());
}
