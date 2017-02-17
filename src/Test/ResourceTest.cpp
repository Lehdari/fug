#include "Test/UnitTests.hpp"

#include "Core/Binary.hpp"
#include "Core/Binary_Init_File.hpp"
#include "Core/Resource.hpp"
#include "Core/ResourceIdMap.hpp"
#include "Core/ResourceManager.hpp"
#include "Core/ResourcePointer.hpp"

#include "Graphics/Canvas_SFML.hpp"
#include "Graphics/ShaderObject.hpp"
#include "Graphics/ShaderObject_Init_Text.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Graphics/ShaderProgram_Init_Default.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/Texture_Init_Binary.hpp"

namespace fug {

    class FUG_RESOURCE(TestResource1) {
    public:
        FUG_RESOURCE_INIT_DESTROY_DECL

        int a;
        int b;
    };

    class FUG_RESOURCE(TestResource2) {
    public:
        FUG_RESOURCE_INIT_DESTROY_DECL

        float a;
        float b;
    };

    class FUG_RESOURCE(TestResource3) {
    public:
        FUG_RESOURCE_INIT_DESTROY_DECL

        double a;
        double b;
    };

    struct TestResource1_Init_Default {
        int a;
        int b;
    };

    struct TestResource2_Init_TestResource1 {
        float a;
        float b;
    };

    struct TestResource3_Init_TestResource2 {
        double a;
        double b;
    };

    FUG_RESOURCE_INIT(TestResource1, TestResource1_Init_Default)
    {
        printf("Initializing TestResource1 with TestResource1_Init_Default\n");
        printf("InitInfo: a: %d b: %d\n", initInfo.a, initInfo.b);
        printf("InitResources: {");
        for (auto& r : initResources)
            printf("%llu,", (long long unsigned)r);
        printf("}\n");
    }

    FUG_RESOURCE_DESTROY(TestResource1, TestResource1_Init_Default)
    {
        printf("Destroying TestResource1(TestResource1_Init_Default)\n");
    }

    FUG_RESOURCE_INIT(TestResource2, TestResource2_Init_TestResource1)
    {
        printf("Initializing TestResource1 with TestResource2_Init_TestResource1\n");
        printf("InitInfo: a: %0.4f b: %0.4f\n", initInfo.a, initInfo.b);
        printf("InitResources: {");
        for (auto& r : initResources)
            printf("%llu,", (long long unsigned)r);
        printf("}\n");

        auto tr1Ptr = FUG_RESOURCE_MANAGER.getResource<TestResource1>(initResources[0]);

        printf("initResource[0]: a: %d b: %d\n", tr1Ptr->a, tr1Ptr->b);

        a = tr1Ptr->a;
        b = tr1Ptr->b;
    }

    FUG_RESOURCE_DESTROY(TestResource2, TestResource2_Init_TestResource1)
    {
        printf("Destroying TestResource1(TestResource2_Init_TestResource1)\n");
    }

    FUG_RESOURCE_INIT(TestResource3, TestResource3_Init_TestResource2)
    {
        printf("Initializing TestResource2 with TestResource3_Init_TestResource2\n");
        printf("InitInfo: a: %0.4f b: %0.4f\n", initInfo.a, initInfo.b);
        printf("InitResources: {");
        for (auto& r : initResources)
            printf("%llu,", (long long unsigned)r);
        printf("}\n");

        auto tr1Ptr = FUG_RESOURCE_MANAGER.getResource<TestResource2>(initResources[0]);

        a = tr1Ptr->a;
        b = tr1Ptr->b;
    }

    FUG_RESOURCE_DESTROY(TestResource3, TestResource3_Init_TestResource2)
    {
        printf("Destroying TestResource2(TestResource3_Init_TestResource2)\n");
    }

}

FUG_UNIT_TEST(resourceTest) {
    using namespace fug;

    auto id1 = FUG_RESOURCE_ID_MAP.getId("test1");
    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource1, TestResource1_Init_Default>
        (id1, {1, 2}, {101, 102, 103});

    auto id2 = FUG_RESOURCE_ID_MAP.getId("test2");
    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource1, TestResource1_Init_Default>
        (id2, {2, 3}, {111, 112, 113});

    auto id3 = FUG_RESOURCE_ID_MAP.getId("test3");
    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource1, TestResource1_Init_Default>
        (id3, {3, 4}, {121, 122, 123});

    auto id4 = FUG_RESOURCE_ID_MAP.getId("test3");
    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource2, TestResource2_Init_TestResource1>
        (id4, {4.5f, 5.5f}, {3});

    auto r2p1 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(id2);
    auto r3p1 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(id3);
    auto r3p2 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(id3);
    auto r1p1 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(id1);
    auto r4p1 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(id4);

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
    auto texBinId = FUG_RESOURCE_ID_MAP.getId("purjoBin");
    FUG_RESOURCE_MANAGER.addResourceInfo<Binary, BinaryInitInfo_File>
        (texBinId, BinaryInitInfo_File{"../res/textures/test_purjo.png"});
    auto texBinPtr = FUG_RESOURCE_MANAGER.getResource<Binary>(texBinId);

#if 0
    auto srcResPtr = FUG_RESOURCE_MANAGER.getResource<Binary>(5);
    //auto srcResPtr1 = FUG_RESOURCE_MANAGER.getResource<Binary>(5);

    printf("%s: get: %p\n", __func__, srcResPtr.get());
    printf("%s, resource pointer buffer: %p\n", __func__, srcResPtr->getBufferPtr());
    printf("%s\n", srcResPtr->getBufferPtr());

    FUG_TEST_CASE("ShaderObject");
    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderObject, ShaderObjectInitInfo_Binary>
        (6, ShaderObjectInitInfo_Binary{ShaderObjectInitInfo_Binary::SOURCE_GLSL,
                                            GL_FRAGMENT_SHADER}, {5}, {});
   auto srcResPtr1 = FUG_RESOURCE_MANAGER.getResource<Binary>(5);
   printf("%s: get: %p\n", __func__, srcResPtr1.get());

    FUG_TEST_CASE("ShaderProgram");
    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderProgram, ShaderProgramInitInfo_Default>
        (7, ShaderProgramInitInfo_Default{}, {6}, {});
#endif

    FUG_TEST_CASE("Texture");
    auto texId = FUG_RESOURCE_ID_MAP.getId("purjoTex");
    FUG_RESOURCE_MANAGER.addResourceInfo<Texture, TextureInitInfo_Binary>
        (texId, TextureInitInfo_Binary{TextureInitInfo_Binary::SOURCE_BINARY_PNG,
                                   0, 0, 0, 0}, {texBinId}, {}, true);
    auto texPtr = FUG_RESOURCE_MANAGER.getResource<Texture>(texId);
}


