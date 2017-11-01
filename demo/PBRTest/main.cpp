#include "imgui-fug/imgui/imgui.h"
#include "imgui-fug/imgui_impl_sfml_gl3.h"

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
#include "Graphics/ModelComponent.hpp"

#include "Graphics/ShaderObject.hpp"
#include "Graphics/ShaderObject_Init_Text.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Graphics/ShaderProgram_Init_Default.hpp"

#include "Graphics/Texture.hpp"
#include "Graphics/Texture_Init_Color.hpp"

#include "Graphics/VertexData.hpp"
#include "Graphics/VertexData_Init_Text.hpp"
#include "Graphics/VertexData_Init_UVSphere.hpp"

#include "Graphics/Canvas_SFML.hpp"
#include "Graphics/Renderer.hpp"

static const ImVec4 ironSpherePos(1.f,0.5f,0.f,1.f);
static const ImVec4 copperSpherePos(-1.f,0.5f,0.f,1.f);

int main(void)
{
    using namespace fug;
    Canvas_SFML c;
    sf::Window* wPtr = c.getWindow();

    // Bind imgui
    ImGui_ImplSFMLGL3_Init(wPtr);

    // Load resources
    ResourceLoader resourceLoader("pbr_test.stfu");
    resourceLoader.load();

    // Set components
    auto ironMaterialResPtr = FUG_RESOURCE_MANAGER.getResource<Material>(FUG_RESOURCE_ID_MAP.getId("material_iron"));
    auto copperMaterialResPtr = FUG_RESOURCE_MANAGER.getResource<Material>(FUG_RESOURCE_ID_MAP.getId("material_copper"));
    auto redPlasticMaterialResPtr = FUG_RESOURCE_MANAGER.getResource<Material>(FUG_RESOURCE_ID_MAP.getId("material_red_plastic"));
    auto sphereMeshResPtr = FUG_RESOURCE_MANAGER.getResource<Mesh>(FUG_RESOURCE_ID_MAP.getId("mesh_uvsphere"));
    auto quadMeshResPtr = FUG_RESOURCE_MANAGER.getResource<Mesh>(FUG_RESOURCE_ID_MAP.getId("mesh_quad"));
    ModelComponent ironSphereModelComp(ironMaterialResPtr, sphereMeshResPtr);
    ModelComponent copperSphereModelComp(redPlasticMaterialResPtr, sphereMeshResPtr);
    ModelComponent quadModelComp(redPlasticMaterialResPtr, quadMeshResPtr);
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
            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...

        Matrix4Glf translation;
        translation << 1.f, 0.f, 0.f, ironSpherePos.x,
                       0.f, 1.f, 0.f, ironSpherePos.y,
                       0.f, 0.f, 1.f, ironSpherePos.z,
                       0.f, 0.f, 0.f,             1.f;

        TransformComponent transform;
        transform.transform = translation;
        renderer(ironSphereModelComp, transform);
        translation << 1.f, 0.f, 0.f, copperSpherePos.x,
                       0.f, 1.f, 0.f, copperSpherePos.y,
                       0.f, 0.f, 1.f, copperSpherePos.z,
                       0.f, 0.f, 0.f,             1.f;

        transform.transform = translation;
        renderer(copperSphereModelComp, transform);
        translation << 1.f, 0.f, 0.f, 0.f,
                       0.f, 1.f, 0.f, 0.f,
                       0.f, 0.f, 1.f, 0.f,
                       0.f, 0.f, 0.f, 1.f;
        Matrix4Glf rotMatX;
        rotMatX << 1.f,         0.f,          0.f,  0.f,
                   0.f, cosf(1.57f), -sinf(1.57f), -1.f,
                   0.f, sinf(1.57f),  cosf(1.57f),  0.f,
                   0.f ,        0.f,          0.f, 1.f;
        Matrix4Glf scaleMat;
        scaleMat << 10.f,  0.f,  0.f, 0.f,
                     0.f, 10.f,  0.f, 0.f,
                     0.f,  0.f, 10.f, 0.f,
                     0.f,  0.f,  0.f, 1.f;
        transform.transform = translation * rotMatX * scaleMat;
        renderer(quadModelComp, transform);

        ImGui::Render();
        // end the current frame (internally swaps the front and back buffers)
        wPtr->display();
    }
    return 0;
}
