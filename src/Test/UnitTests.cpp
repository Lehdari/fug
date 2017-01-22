#include "Test/UnitTests.hpp"

#include <cstdio>

#include "Core/Scene.hpp"
#include "Test/TestVisitors.hpp"
#include "Test/TestComponents.hpp"

#define TEST(M) std::cout<<"Testing "<<M<<" ... "<<std::endl;
#define TEST_EQ(F,S) if(F!=S)throw;
#define TEST_INEQ(F,S) if(F==S)throw;

#include "Core/Binary.hpp"
#include "Core/Binary_Init_File.hpp"
#include "Core/ResourceManager.hpp"
#include "Core/ResourcePointer.hpp"
#include "Test/TestResources.hpp"
#include "Test/TestResources_Init.hpp"
#include "Test/TestEvents.hpp"
#include "Core/EventManager.hpp"
#include "Core/Utility.hpp"

// Graphics includes
#include "Graphics/Canvas.hpp"
#include "Graphics/Canvas_SFML.hpp"

#include "Graphics/Material.hpp"
#include "Graphics/Material_Init.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/Mesh_Init.hpp"
#include "Graphics/MeshComponent.hpp"

#include "Graphics/Renderer.hpp"
#include "Graphics/SpriteRenderer.hpp"

#include "Graphics/ShaderObject.hpp"
#include "Graphics/ShaderObject_Init_Binary.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Graphics/ShaderProgram_Init_Default.hpp"

#include "Graphics/SpriteMeshComponent.hpp"
#include "Graphics/SpriteMaterial.hpp"
#include "Graphics/SpriteMaterial_Init.hpp"

#include "Graphics/SpriteMesh.hpp"
#include "Graphics/SpriteMesh_Init.hpp"
#include "Graphics/SpriteMeshComponent.hpp"

#include "Graphics/Texture.hpp"
#include "Graphics/Texture_Init_Binary.hpp"

#include "Graphics/VertexData.hpp"
#include "Graphics/VertexData_Init.hpp"

void fug::sceneTest(void) {
    /*EId nid[10] = {0};
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

    FUG_SCENE.print();*/
}

void fug::resourceTest(void) {
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

void fug::gfxResourceTest(void) {
    // Assumes a test file
    fug::Canvas_SFML canvas;
    canvas.display();

    TEST("Binary");
    FUG_RESOURCE_MANAGER.addResourceInfo<Binary, BinaryInitInfo_File>
        (5, BinaryInitInfo_File{"../res/textures/test_purjo.glsl"});

#if 1
    auto srcResPtr = FUG_RESOURCE_MANAGER.getResource<Binary>(5);
    //auto srcResPtr1 = FUG_RESOURCE_MANAGER.getResource<Binary>(5);

    printf("%s: get: %p\n", __func__, srcResPtr.get());
    printf("%s, resource pointer buffer: %p\n", __func__, srcResPtr->getBufferPtr());
    printf("%s\n", srcResPtr->getBufferPtr());
#endif

    TEST("ShaderObject");
    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderObject, ShaderObjectInitInfo_Binary>
        (6, ShaderObjectInitInfo_Binary{ShaderObjectInitInfo_Binary::SOURCE_GLSL,
                                        GL_FRAGMENT_SHADER}, {5}, {});
    auto srcResPtr1 = FUG_RESOURCE_MANAGER.getResource<Binary>(5);
    printf("%s: get: %p\n", __func__, srcResPtr1.get());

    TEST("ShaderProgram");
    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderProgram, ShaderProgramInitInfo_Default>
        (7, ShaderProgramInitInfo_Default{}, {6}, {});

    TEST("Texture");
    FUG_RESOURCE_MANAGER.addResourceInfo<Binary, BinaryInitInfo_File>
        (8, BinaryInitInfo_File{"../res/textures/test_purjo.glsl"});
    FUG_RESOURCE_MANAGER.addResourceInfo<Texture, TextureInitInfo_Binary>
        (9, TextureInitInfo_Binary{TextureInitInfo_Binary::SOURCE_BINARY_PNG,
                                   0, 0, 0, 0}, {8}, {});
}


void fug::eventTest(void) {

	std::cout << "Testing events\n\n";

	TEST("push")
	for (uint64_t i = 1; i<11; i++) {
		FUG_EVENT_MANAGER.pushEvent(10*i, 123);
	}

	TEST("getMailbox")
	auto mailbox = FUG_EVENT_MANAGER.getMailbox<uint64_t>(123);

	TEST("begin, end");
	auto begin = mailbox.begin();
	auto end = mailbox.end();
	std::cout << " -> " << begin << std::endl
			  << " -> " << end << std::endl;

	TEST("iteration")
	for (; begin != end; ++begin) {
		std::cout << begin->data << "  ";
	}
	std::cout << std::endl;
	
	TEST("flush")
	FUG_EVENT_MANAGER.flushEvents<uint64_t>(123);
	auto mailbox2 = FUG_EVENT_MANAGER.getMailbox<uint64_t>(123);
	begin = mailbox2.begin();
	end = mailbox2.end();
	std::cout << "should be empty:" << std::endl;
	for (; begin != end; ++begin) {
		std::cout << begin->data << "  ";
	}
	std::cout << std::endl;

	TEST("accessing")
	end->data = 123;
	TEST_EQ(end->data, 123)

	TEST("dereferencing")
	(*end).data = 321;
	TEST_INEQ((*end).data, 123)
	
}

void fug::drawTest()
{
    Canvas_SFML c;
    sf::Window* wPtr = c.getWindow();

    // Load resources

    // SpriteTexture
    FUG_RESOURCE_MANAGER.addResourceInfo<Binary, BinaryInitInfo_File>
    (100, BinaryInitInfo_File{"../res/textures/test_purjo.png"});
    FUG_RESOURCE_MANAGER.addResourceInfo<Texture, TextureInitInfo_Binary>
    (101, TextureInitInfo_Binary{TextureInitInfo_Binary::SOURCE_BINARY_PNG,
        GL_CLAMP_TO_BORDER,
        GL_CLAMP_TO_BORDER,
        GL_NEAREST,
        GL_NEAREST},
     {100}, {}, true);

    // Sprite ShaderProgram
    FUG_RESOURCE_MANAGER.addResourceInfo<Binary, BinaryInitInfo_File>
    (102, BinaryInitInfo_File{"../src/Graphics/shader/sprite_vert.glsl"});
    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderObject, ShaderObjectInitInfo_Binary>
    (103, ShaderObjectInitInfo_Binary{ShaderObjectInitInfo_Binary::SOURCE_GLSL,
        GL_VERTEX_SHADER}, {102}, {});

    FUG_RESOURCE_MANAGER.addResourceInfo<Binary, BinaryInitInfo_File>
    (104, BinaryInitInfo_File{"../src/Graphics/shader/sprite_frag.glsl"});
    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderObject, ShaderObjectInitInfo_Binary>
    (105, ShaderObjectInitInfo_Binary{ShaderObjectInitInfo_Binary::SOURCE_GLSL,
        GL_FRAGMENT_SHADER}, {104}, {});

    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderProgram, ShaderProgramInitInfo_Default>
        (106, ShaderProgramInitInfo_Default{}, {103,105}, {});

    // SpriteMaterial
    FUG_RESOURCE_MANAGER.addResourceInfo<SpriteMaterial, SpriteMaterialInitInfo_Default>
    (107, SpriteMaterialInitInfo_Default{{"diffuseSampler"},
                                        {"uModelToClip"},
                                        {"uSpriteW", "uSpriteH"},
                                        {"uFrameRow", "uFrameColumn"},
                                        32, 32},
                                        {}, {106,101});
    
    // SpriteMesh
    FUG_RESOURCE_MANAGER.addResourceInfo<SpriteMesh, SpriteMeshInitInfo_Default>
    (108, SpriteMeshInitInfo_Default(), {}, {107});

    // SpriteMeshComponent
    auto spriteMeshResPtr = FUG_RESOURCE_MANAGER.getResource<SpriteMesh>(108);
    SpriteMeshComponent spriteMeshComp(spriteMeshResPtr);
    
    // Default ShaderProgram
    FUG_RESOURCE_MANAGER.addResourceInfo<Binary, BinaryInitInfo_File>
    (109, BinaryInitInfo_File{"../src/Graphics/shader/default_vert.glsl"});

    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderObject, ShaderObjectInitInfo_Binary>
    (110, ShaderObjectInitInfo_Binary{ShaderObjectInitInfo_Binary::SOURCE_GLSL,
        GL_VERTEX_SHADER}, {109}, {});

    FUG_RESOURCE_MANAGER.addResourceInfo<Binary, BinaryInitInfo_File>
    (111, BinaryInitInfo_File{"../src/Graphics/shader/default_frag.glsl"});

    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderObject, ShaderObjectInitInfo_Binary>
    (112, ShaderObjectInitInfo_Binary{ShaderObjectInitInfo_Binary::SOURCE_GLSL,
        GL_FRAGMENT_SHADER}, {111}, {});

    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderProgram, ShaderProgramInitInfo_Default>
    (113, ShaderProgramInitInfo_Default{}, {110,112}, {}, true);

    // Cube Texture
    FUG_RESOURCE_MANAGER.addResourceInfo<Binary, BinaryInitInfo_File>
    (114, BinaryInitInfo_File{"../res/textures/kuutio.png"});
    FUG_RESOURCE_MANAGER.addResourceInfo<Texture, TextureInitInfo_Binary>
    (115, TextureInitInfo_Binary{TextureInitInfo_Binary::SOURCE_BINARY_PNG,
        GL_CLAMP_TO_BORDER,
        GL_CLAMP_TO_BORDER,
        GL_NEAREST,
        GL_NEAREST},
     {114}, {}, true);

    // Cube Material
    FUG_RESOURCE_MANAGER.addResourceInfo<Material, MaterialInitInfo_Default>
    (116, MaterialInitInfo_Default{{"diffuseSampler"},
                                   {"uModelToClip", "uModelToCam", "uNormalToCam"},
                                   {"uSpecularCol"},
                                   {"uSpecularExp"},
                                   Vector3Glf(0.1f, 0.1f, 0.1f), 0.5f},
                                   {}, {113,115}, true);
    
    // Cube VertexData
    FUG_RESOURCE_MANAGER.addResourceInfo<Binary, BinaryInitInfo_File>
    (117, BinaryInitInfo_File{"../res/meshes/kuutio.obj"});
    FUG_RESOURCE_MANAGER.addResourceInfo<VertexData, VertexDataInitInfo_Binary>
    (118, VertexDataInitInfo_Binary{VertexDataInitInfo_Binary::SOURCE_BINARY_OBJ},
        {117}, {}, true);
    
    // Cube Mesh
    FUG_RESOURCE_MANAGER.addResourceInfo<Mesh, MeshInitInfo_Default>
    (119, MeshInitInfo_Default(), {118}, {116});
    
    // Cube MeshComponent
    auto cubeMeshResPtr = FUG_RESOURCE_MANAGER.getResource<Mesh>(119);
    MeshComponent cubeMeshComp(cubeMeshResPtr);
    
    Renderer renderer(Vector3Glf(0.f, 0.f, -3.f), Vector3Glf(0.f, 0.f, 1.f),
                      Vector3Glf(0.f, 1.f, 0.f), 90.f, 1280/720.f, 1.f, 10.f);
    
    SpriteRenderer spriteRenderer(Vector3Glf(0.f, 0.f, -3.f), Vector3Glf(0.f, 0.f, 1.f),
                      Vector3Glf(0.f, 1.f, 0.f), 90.f, 1280/720.f, 1.f, 10.f);

    bool running = true;
    unsigned frame = 0;
    unsigned anim = 0;
    unsigned column = 0;
    while (running)
    {
        // handle events
        sf::Event event;
        while (wPtr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (frame % 16 == 15) {
            column = column < 7 ? column + 1 : 0;
            if (column == 0) anim = anim < 7 ? anim + 1 : 0;
        }
        // draw...
        spriteRenderer(spriteMeshComp);
        renderer(cubeMeshComp);

        // end the current frame (internally swaps the front and back buffers)
        wPtr->display();
        frame++;
    }
}

void fug::unitTest(void) {
    //sceneTest();
    //resourceTest();
    //gfxResourceTest();
	//eventTest();
	drawTest();
}
