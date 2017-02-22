#include "Test/UnitTests.hpp"

#include "Engine/ResourceLoader.hpp"
#include "Core/ResourceManager.hpp"
#include "Core/Text.hpp"
#include "Core/Text_Init_File.hpp"

#include <iostream>


using namespace fug;


FUG_UNIT_TEST(resourceLoaderTest) {
    ResourceLoader resourceLoader("resources.stfu");
    resourceLoader.load();
    auto vertResPtr = FUG_RESOURCE_MANAGER.getResource<Text>
        (FUG_RESOURCE_ID_MAP.getId("binary_shader_default_vert"));
    // TODO
    FUG_LOG(LogLevel::Debug)("%s\n", vertResPtr->getBufferPtr());
}
