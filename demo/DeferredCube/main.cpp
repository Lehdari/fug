#include "imgui-fug/imgui/imgui.h"
#include "imgui-fug/imgui_impl_sfml_gl3.h"

#include "Core/ResourceManager.hpp"

#include "Core/Binary.hpp"
#include "Core/Binary_Init_File.hpp"
#include "Core/Text.hpp"
#include "Core/Text_Init_File.hpp"
#include "Core/Scene.hpp"

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
#include "Graphics/Texture_Init_Binary.hpp"

#include "Graphics/VertexData.hpp"
#include "Graphics/VertexData_Init_Text.hpp"

#include "Graphics/Canvas_SFML.hpp"
#include "Graphics/GeometryPassVisitor.hpp"
#include "Graphics/GBuffer.hpp"

#include "Graphics/DirectionalLightComponent.hpp"

int main(void)
{
    using namespace fug;
    Canvas_SFML c;
    sf::Window* wPtr = c.getWindow();

    // Bind imgui
    ImGui_ImplSFMLGL3_Init(wPtr);

    // Load resources
    ResourceLoader resourceLoader("deferred_cube.stfu");
    resourceLoader.load();

    // Set up scene

    FUG_SCENE.addEntity();

    auto cubeMeshResPtr = FUG_RESOURCE_MANAGER.getResource<Mesh>(
                            FUG_RESOURCE_ID_MAP.getId("mesh_cube"));
    FUG_SCENE.addComponent(MeshComponent(cubeMeshResPtr));

    FUG_SCENE.addComponent(TransformComponent());

    // DirectionalLightComponent

    auto dirLightShaderPtr = FUG_RESOURCE_MANAGER.getResource<ShaderProgram>(
                         FUG_RESOURCE_ID_MAP.getId("shaderprogram_deferred_dirlightpass"));
    DirectionalLightComponent dirLight(dirLightShaderPtr,
                                       std::vector<std::string>({"depthMap", "diffuseMap", "normalMap", "specularMap"}),
                                       "uLightDir", Vector3Glf(-1.f, -1.f, 1.f),
                                       "uLightCol", Vector3Glf(1.f, 1.f, 1.f),
                                       "uDirectInt", 1.f, "uAmbientInt", 0.2f);

    // Quad MeshComponent
    auto quadMeshResPtr = FUG_RESOURCE_MANAGER.getResource<Mesh>(
                            FUG_RESOURCE_ID_MAP.getId("mesh_quad"));
    MeshComponent quadMeshComp(quadMeshResPtr);

    Camera cam(Vector3Glf(0.f, 0.f, -3.f), Vector3Glf(0.f, 0.f, 1.f),
               Vector3Glf(0.f, 1.f, 0.f), 90.f, 1280/720.f, 1.f, 10.f);

    GBuffer gBuffer(1280, 720,{GL_R32F, GL_RGBA16, GL_RGB32F, GL_RGBA16},
                              { GL_RED,   GL_RGBA,    GL_RGB,   GL_RGBA});

    bool running = true;
    ImVec4 pos(0.f, 0.f, 0.f, 0.f);
    float rotX = 0.f;
    float rotY = 0.f;
    int currentMode = 0;
    auto dirlightPassID = FUG_RESOURCE_MANAGER.getResource<ShaderProgram>(
        FUG_RESOURCE_ID_MAP.getId("shaderprogram_deferred_dirlightpass"))->getId();

    // Setup geometry pass

    // Main loop
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
            ImGui::SliderFloat("rotX", &rotX, -PI, PI);
            ImGui::SliderFloat("rotY", &rotY, -PI, PI);
            const char* renderModes[] = { "Depth", "Diffuse",
                                          "Normals", "Specular" };
            ImGui::ListBox("", &currentMode, renderModes, 4, 4);
            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        // draw...

        Matrix4Glf translation;
        translation << 1.f, 0.f, 0.f, pos.x,
                       0.f, 1.f, 0.f, pos.y,
                       0.f, 0.f, 1.f, pos.z,
                       0.f, 0.f, 0.f,   1.f;
        Matrix4Glf rotXMat;
        rotXMat << 1.f,        0.f,         0.f, 0.f,
                   0.f, cosf(rotX), -sinf(rotX), 0.f,
                   0.f, sinf(rotX),  cosf(rotX), 0.f,
                   0.f,        0.f,         0.f, 1.f;
        Matrix4Glf rotYMat;
        rotYMat <<  cosf(rotY), 0.f, sinf(rotY), 0.f,
                           0.f, 1.f,        0.f, 0.f,
                   -sinf(rotY), 0.f, cosf(rotY), 0.f,
                           0.f, 0.f,        0.f, 1.f;
        // TODO: Add Transform visitor here, init transform with identity?
        // transform.transform = translation * rotXMat * rotYMat;
        gBuffer.bindWrite();
        GeometryPassVisitor gPVisitor(cam); // TODO: this really should be done with visitor.init() or somesuch
        FUG_SCENE.accept(gPVisitor);
        glDepthMask(GL_FALSE);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        glBlendFunc(GL_ONE, GL_ONE);
        gBuffer.bindRead();
        glClear(GL_COLOR_BUFFER_BIT);
        dirLight.bind(cam.getView());
        glUniform1i(glGetUniformLocation(dirlightPassID, "uOnlyDepth"),
                    currentMode == 0);
        glUniform1i(glGetUniformLocation(dirlightPassID, "uOnlyDiffuse"),
                    currentMode == 1);
        glUniform1i(glGetUniformLocation(dirlightPassID, "uOnlyNormal"),
                    currentMode == 2);
        glUniform1i(glGetUniformLocation(dirlightPassID, "uOnlySpecular"),
                    currentMode == 3);
        quadMeshComp.draw();

        ImGui::Render();
        // end the current frame (internally swaps the front and back buffers)
        wPtr->display();
    }
    return 0;
}
