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

    auto whiteMaterialID = FUG_RESOURCE_ID_MAP.getId("material_white");

    auto vertDataID = FUG_RESOURCE_ID_MAP.getId("vertexdata_cube");
    
    // Cube Mesh
    FUG_RESOURCE_MANAGER.addResourceInfo<Mesh, MeshInitInfo_Default>
    (119, MeshInitInfo_Default(), {vertDataID}, {whiteMaterialID});

    // Cube MeshComponent
    auto cubeMeshResPtr = FUG_RESOURCE_MANAGER.getResource<Mesh>(119);
    MeshComponent cubeMeshComp(cubeMeshResPtr);

    vertDataID = FUG_RESOURCE_ID_MAP.getId("vertexdata_quad");

    // Quad Mesh
    FUG_RESOURCE_MANAGER.addResourceInfo<Mesh, MeshInitInfo_Default>
    (139, MeshInitInfo_Default(), {vertDataID}, {whiteMaterialID});

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
