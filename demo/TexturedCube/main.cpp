#include "imgui-fug/imgui/imgui.h"
#include "imgui-fug/imgui_impl_sfml_gl3.h"

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

#include "Graphics/Texture.hpp"
#include "Graphics/Texture_Init_Binary.hpp"

#include "Graphics/VertexData.hpp"
#include "Graphics/VertexData_Init_Text.hpp"

#include "Graphics/Canvas_SFML.hpp"
#include "Graphics/Renderer.hpp"

int main(void)
{
    using namespace fug;
    Canvas_SFML c;
    sf::Window* wPtr = c.getWindow();

    // Bind imgui
    ImGui_ImplSFMLGL3_Init(wPtr);

    // Load resources

    // Default ShaderProgram
    FUG_RESOURCE_MANAGER.addResourceInfo<Text, TextInitInfo_File>
    (109, TextInitInfo_File{std::string(FUG_RES_DIRECTORY) + "../res/shader/default_vert.glsl"});

    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderObject, ShaderObjectInitInfo_Text>
    (110, ShaderObjectInitInfo_Text{GL_VERTEX_SHADER}, {109}, {});

    FUG_RESOURCE_MANAGER.addResourceInfo<Text, TextInitInfo_File>
    (111, TextInitInfo_File{std::string(FUG_RES_DIRECTORY) + "../res/shader/default_frag.glsl"});

    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderObject, ShaderObjectInitInfo_Text>
    (112, ShaderObjectInitInfo_Text{GL_FRAGMENT_SHADER}, {111}, {});

    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderProgram, ShaderProgramInitInfo_Default>
    (113, ShaderProgramInitInfo_Default{}, {110,112}, {}, true);

    // Cube Texture
    FUG_RESOURCE_MANAGER.addResourceInfo<Binary, BinaryInitInfo_File>
    (114, BinaryInitInfo_File{std::string(FUG_RES_DIRECTORY) + "../res/textures/cube.png"});
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

    Renderer renderer(Vector3Glf(0.f, 0.f, -3.f), Vector3Glf(0.f, 0.f, 1.f),
                      Vector3Glf(0.f, 1.f, 0.f), 90.f, 1280/720.f, 1.f, 10.f);

    bool running = true;
    ImVec4 pos(0.f, 0.f, 0.f, 0.f);
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
            else
            {
                ImGui_ImplSFMLGL3_HandleEvent(event);
            }

        }

        // Simple imgui-window
        ImGui_ImplSFMLGL3_NewFrame();
        // mousepos could be passed to imgui before event-handling and check this
        // to not pass mouse-events to program if hovering
        ImGui::GetIO().MouseDrawCursor = ImGui::IsMouseHoveringAnyWindow();
        {
            ImGui::SliderFloat("x", &pos.x, -2.f, 2.f);
            ImGui::SliderFloat("y", &pos.y, -2.f, 2.f);
            ImGui::SliderFloat("z", &pos.z, -2.f, 2.f);
            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...

        TransformComponent transform;
        transform.transform << 1.f, 0.f, 0.f, pos.x,
                               0.f, 1.f, 0.f, pos.y,
                               0.f, 0.f, 1.f, pos.z,
                               0.f, 0.f, 0.f,   1.f;
        renderer(cubeMeshComp, transform);

        ImGui::Render();
        // end the current frame (internally swaps the front and back buffers)
        wPtr->display();
    }
    return 0;
}
