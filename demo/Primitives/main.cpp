#include "Core/ResourceManager.hpp"

#include "Core/Binary.hpp"
#include "Core/Binary_Init_File.hpp"
#include "Core/Text.hpp"
#include "Core/Text_Init_File.hpp"

#include "Engine/ResourceLoader.hpp"

#include "Graphics/Material.hpp"
#include "Graphics/Material_Init.hpp"

#include "Graphics/Mesh.hpp"
#include "Graphics/Mesh_Init.hpp"
#include "Graphics/MeshComponent.hpp"

#include "Graphics/ShaderObject.hpp"
#include "Graphics/ShaderObject_Init_Text.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Graphics/ShaderProgram_Init_Default.hpp"

#include "Graphics/Texture.hpp"
#include "Graphics/Texture_Init_Color.hpp"

#include "Graphics/VertexData.hpp"
#include "Graphics/VertexData_Init.hpp"

#include "Graphics/Canvas_SFML.hpp"
#include "Graphics/Renderer.hpp"

int main(void)
{
    using namespace fug;
    Canvas_SFML c;
    sf::Window* wPtr = c.getWindow();

    // Load resources

    ResourceLoader resourceLoader("primitives.stfu");
    resourceLoader.load();

    // White Texture
    FUG_RESOURCE_MANAGER.addResourceInfo<Texture, TextureInitInfo_Color>
    (115, TextureInitInfo_Color{Vector4Glf(1.f,1.f,1.f,1.f)},
     {}, {}, true);

    auto shaderProgID = FUG_RESOURCE_ID_MAP.getId("shaderprogram_default");

    // White Material
    FUG_RESOURCE_MANAGER.addResourceInfo<Material, MaterialInitInfo_Default>
    (116, MaterialInitInfo_Default{{"diffuseSampler"},
                                   {"uModelToClip", "uModelToCam", "uNormalToCam"},
                                   {"uSpecularCol"},
                                   {"uSpecularExp"},
                                   Vector3Glf(0.1f, 0.1f, 0.1f), 0.5f},
                                   {}, {shaderProgID,115}, true);

    // Cube VertexData
    FUG_RESOURCE_MANAGER.addResourceInfo<Text, TextInitInfo_File>
    (117, TextInitInfo_File{std::string(FUG_RES_DIRECTORY) + "../res/meshes/cube.obj"});
    FUG_RESOURCE_MANAGER.addResourceInfo<VertexData, VertexDataInitInfo_Text>
    (118, VertexDataInitInfo_Text{VertexDataInitInfo_Text::SOURCE_BINARY_OBJ},
        {117}, {}, true);

    // Cube Mesh
    FUG_RESOURCE_MANAGER.addResourceInfo<Mesh, MeshInitInfo_Default>
    (119, MeshInitInfo_Default(), {118}, {116});

    // Cube MeshComponent
    auto cubeMeshResPtr = FUG_RESOURCE_MANAGER.getResource<Mesh>(119);
    MeshComponent cubeMeshComp(cubeMeshResPtr);

    // Quad VertexData
    FUG_RESOURCE_MANAGER.addResourceInfo<Text, TextInitInfo_File>
    (137, TextInitInfo_File{std::string(FUG_RES_DIRECTORY) + "../res/meshes/quad.obj"});
    FUG_RESOURCE_MANAGER.addResourceInfo<VertexData, VertexDataInitInfo_Text>
    (138, VertexDataInitInfo_Text{VertexDataInitInfo_Text::SOURCE_BINARY_OBJ},
        {137}, {}, true);

    // Quad Mesh
    FUG_RESOURCE_MANAGER.addResourceInfo<Mesh, MeshInitInfo_Default>
    (139, MeshInitInfo_Default(), {138}, {116});

    // Quad MeshComponent
    auto quadMeshResPtr = FUG_RESOURCE_MANAGER.getResource<Mesh>(139);
    MeshComponent quadMeshComp(quadMeshResPtr);

    Renderer renderer(Vector3Glf(0.f, 0.f, -3.f), Vector3Glf(0.f, 0.f, 1.f),
                      Vector3Glf(0.f, 1.f, 0.f), 90.f, 1280/720.f, 1.f, 10.f);

    bool running = true;
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

        // draw...

        TransformComponent transform;
        transform.transform << 1.f, 0.f, 0.f,  2.5f,
                               0.f, 1.f, 0.f,  1.5f,
                               0.f, 0.f, 1.f,  1.5f,
                               0.f, 0.f, 0.f,   1.f;
        renderer(cubeMeshComp, transform);
        transform.transform << 1.f, 0.f, 0.f, -2.5f,
                               0.f, 1.f, 0.f, -1.5f,
                               0.f, 0.f, 1.f,  1.5f,
                               0.f, 0.f, 0.f,   1.f;
        renderer(quadMeshComp, transform);

        // end the current frame (internally swaps the front and back buffers)
        wPtr->display();
    }
    return 0;
}
