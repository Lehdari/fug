#include "Test/UnitTests.hpp"

#include "Graphics/Canvas_SFML.hpp"

#include "Core/Binary.hpp"
#include "Core/Binary_Init_File.hpp"
#include "Core/ResourceManager.hpp"
#include "Core/ResourcePointer.hpp"

#include "Graphics/ShaderObject.hpp"
#include "Graphics/ShaderObject_Init_Binary.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Graphics/ShaderProgram_Init_Default.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/Texture_Init_Binary.hpp"

#include "Test/TestResources.hpp"
#include "Test/TestResources_Init.hpp"


FUG_UNIT_TEST(resourceTest) {
    using namespace fug;
    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource1, TestResource1_Init_Default>
        (1, {1, 2}, {101, 102, 103});
    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource1, TestResource1_Init_Default>
        (2, {2, 3}, {111, 112, 113});
    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource1, TestResource1_Init_Default>
        (3, {3, 4}, {121, 122, 123});


    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource2, TestResource2_Init_TestResource1>
        (4, {4.5f, 5.5f}, {3});

    auto r1p1 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(3);

    //auto tr1Ptr2 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(1);
    //printf("get: %p\n", tr1Ptr2.get());

    //auto r2p1 = FUG_RESOURCE_MANAGER.getResource<TestResource2>(4);


/*
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
*/
}

FUG_UNIT_TEST(gfxResourceTest) {
    using namespace fug;
    // Assumes a test file
    fug::Canvas_SFML canvas;
    canvas.display();

    FUG_TEST_CASE("Binary");
    FUG_RESOURCE_MANAGER.addResourceInfo<Binary, BinaryInitInfo_File>
        (5, BinaryInitInfo_File{"../res/textures/test_purjo.glsl"});

#if 1
    auto srcResPtr = FUG_RESOURCE_MANAGER.getResource<Binary>(5);
    //auto srcResPtr1 = FUG_RESOURCE_MANAGER.getResource<Binary>(5);

    printf("%s: get: %p\n", __func__, srcResPtr.get());
    printf("%s, resource pointer buffer: %p\n", __func__, srcResPtr->getBufferPtr());
    printf("%s\n", srcResPtr->getBufferPtr());
#endif

    FUG_TEST_CASE("ShaderObject");
    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderObject, ShaderObjectInitInfo_Binary>
        (6, ShaderObjectInitInfo_Binary{ShaderObjectInitInfo_Binary::SOURCE_GLSL,
                                        GL_FRAGMENT_SHADER}, {5}, {});
    auto srcResPtr1 = FUG_RESOURCE_MANAGER.getResource<Binary>(5);
    printf("%s: get: %p\n", __func__, srcResPtr1.get());

    FUG_TEST_CASE("ShaderProgram");
    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderProgram, ShaderProgramInitInfo_Default>
        (7, ShaderProgramInitInfo_Default{}, {6}, {});

    FUG_TEST_CASE("Texture");
    FUG_RESOURCE_MANAGER.addResourceInfo<Binary, BinaryInitInfo_File>
        (8, BinaryInitInfo_File{"../res/textures/test_purjo.glsl"});
    FUG_RESOURCE_MANAGER.addResourceInfo<Texture, TextureInitInfo_Binary>
        (9, TextureInitInfo_Binary{TextureInitInfo_Binary::SOURCE_BINARY_PNG,
                                   0, 0, 0, 0}, {8}, {});
}


