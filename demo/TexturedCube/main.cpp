#include "Core/ResourceManager.hpp"

#include "Core/Binary.hpp"
#include "Core/Binary_Init_File.hpp"
#include "Core/Text.hpp"
#include "Core/Text_Init_File.hpp"

#include "Graphics/Material.hpp"
#include "Graphics/Material_Init.hpp"

#include "Graphics/Mesh.hpp"
#include "Graphics/Mesh_Init.hpp"
#include "Graphics/MeshComponent.hpp"

#include "Graphics/ShaderObject.hpp"
#include "Graphics/ShaderObject_Init_Text.hpp"
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

#include "Graphics/Canvas_SFML.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/SpriteRenderer.hpp"

int main(void)
{
    using namespace fug;
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
    FUG_RESOURCE_MANAGER.addResourceInfo<Text, TextInitInfo_File>
    (102, TextInitInfo_File{"../res/shader/sprite_vert.glsl"});
    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderObject, ShaderObjectInitInfo_Text>
    (103, ShaderObjectInitInfo_Text{GL_VERTEX_SHADER}, {102}, {});

    FUG_RESOURCE_MANAGER.addResourceInfo<Text, TextInitInfo_File>
    (104, TextInitInfo_File{"../res/shader/sprite_frag.glsl"});
    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderObject, ShaderObjectInitInfo_Text>
    (105, ShaderObjectInitInfo_Text{GL_FRAGMENT_SHADER}, {104}, {});

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
    FUG_RESOURCE_MANAGER.addResourceInfo<Text, TextInitInfo_File>
    (109, TextInitInfo_File{"../res/shader/default_vert.glsl"});

    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderObject, ShaderObjectInitInfo_Text>
    (110, ShaderObjectInitInfo_Text{GL_VERTEX_SHADER}, {109}, {});

    FUG_RESOURCE_MANAGER.addResourceInfo<Text, TextInitInfo_File>
    (111, TextInitInfo_File{"../res/shader/default_frag.glsl"});

    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderObject, ShaderObjectInitInfo_Text>
    (112, ShaderObjectInitInfo_Text{GL_FRAGMENT_SHADER}, {111}, {});

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
    FUG_RESOURCE_MANAGER.addResourceInfo<Text, TextInitInfo_File>
    (117, TextInitInfo_File{"../res/meshes/kuutio.obj"});
    FUG_RESOURCE_MANAGER.addResourceInfo<VertexData, VertexDataInitInfo_Text>
    (118, VertexDataInitInfo_Text{VertexDataInitInfo_Text::SOURCE_BINARY_OBJ},
        {117}, {}, true);

    // Cube Mesh
    FUG_RESOURCE_MANAGER.addResourceInfo<Mesh, MeshInitInfo_Default>
    (119, MeshInitInfo_Default(), {118}, {116});

    // Cube MeshComponent
    auto cubeMeshResPtr = FUG_RESOURCE_MANAGER.getResource<Mesh>(119);
    MeshComponent cubeMeshComp(cubeMeshResPtr);

    // Cube VertexData
    FUG_RESOURCE_MANAGER.addResourceInfo<Text, TextInitInfo_File>
    (137, TextInitInfo_File{"../res/meshes/kuutio.obj"});
    FUG_RESOURCE_MANAGER.addResourceInfo<VertexData, VertexDataInitInfo_Text>
    (138, VertexDataInitInfo_Text{VertexDataInitInfo_Text::SOURCE_BINARY_OBJ},
        {137}, {}, true);

    // Cube Mesh
    FUG_RESOURCE_MANAGER.addResourceInfo<Mesh, MeshInitInfo_Default>
    (139, MeshInitInfo_Default(), {138}, {116});

    // Cube MeshComponent
    auto cubeMeshResPtr2 = FUG_RESOURCE_MANAGER.getResource<Mesh>(139);
    MeshComponent cubeMeshComp2(cubeMeshResPtr2);

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

        TransformComponent transform;
        transform.transform << 1.f, 0.f, 0.f, 1.f,
                               0.f, 1.f, 0.f, -1.f,
                               0.f, 0.f, 1.f, 0.f,
                               0.f, 0.f, 0.f, 1.f;
        spriteRenderer(spriteMeshComp, transform);
        transform.transform << 1.f, 0.f, 0.f, -2.5f,
                               0.f, 1.f, 0.f,  1.5f,
                               0.f, 0.f, 1.f,  1.5f,
                               0.f, 0.f, 0.f,   1.f;
        renderer(cubeMeshComp, transform);
        transform.transform << 1.f, 0.f, 0.f, -2.5f,
                               0.f, 1.f, 0.f, -1.5f,
                               0.f, 0.f, 1.f,  1.5f,
                               0.f, 0.f, 0.f,   1.f;
        renderer(cubeMeshComp2, transform);

        // end the current frame (internally swaps the front and back buffers)
        wPtr->display();
        frame++;
    }
    return 0;
}
