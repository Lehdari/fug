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

namespace {
    const float FOV = 90.f * PI / 180.f;
    const float Z_NEAR = 0.1f;
    const float Z_FAR = 100.f;
    const float MAX_PITCH = PI * 0.4999f;
    int CENTER_X = 1280 * 0.5;
    int CENTER_Y = 720 * 0.5;
}

int main(void)
{
    using namespace fug;
    Canvas_SFML c;
    sf::Window* window = c.getWindow();

    // Bind imgui
    ImGui_ImplSFMLGL3_Init(window);

    // Load resources
    ResourceLoader resourceLoader("pbr_test.stfu");
    resourceLoader.load();

    auto ironMaterialResPtr = FUG_RESOURCE_MANAGER.getResource<Material>(FUG_RESOURCE_ID_MAP.getId("material_iron"));
    auto copperMaterialResPtr = FUG_RESOURCE_MANAGER.getResource<Material>(FUG_RESOURCE_ID_MAP.getId("material_copper"));
    auto redPlasticMaterialResPtr = FUG_RESOURCE_MANAGER.getResource<Material>(FUG_RESOURCE_ID_MAP.getId("material_red_plastic"));
    auto sphereMeshResPtr = FUG_RESOURCE_MANAGER.getResource<Mesh>(FUG_RESOURCE_ID_MAP.getId("mesh_uvsphere"));
    auto quadMeshResPtr = FUG_RESOURCE_MANAGER.getResource<Mesh>(FUG_RESOURCE_ID_MAP.getId("mesh_quad"));

    // Set up scene
    Matrix4Glf translation;
    translation << 1.f, 0.f, 0.f,  0.f,
                   0.f, 1.f, 0.f,  0.f,
                   0.f, 0.f, 1.f, -2.f,
                   0.f, 0.f, 0.f,  1.f;
    Matrix4Glf rotMatX;
    rotMatX << 1.f,         0.f,          0.f,  0.f,
               0.f, cosf(1.57f), -sinf(1.57f), -1.f,
               0.f, sinf(1.57f),  cosf(1.57f),  0.f,
               0.f ,        0.f,          0.f,  1.f;
    Matrix4Glf scaleMat;
    scaleMat << 10.f,  0.f,  0.f, 0.f,
                 0.f, 10.f,  0.f, 0.f,
                 0.f,  0.f, 10.f, 0.f,
                 0.f,  0.f,  0.f, 1.f;
    TransformComponent floorTransform;
    floorTransform.transform = translation * rotMatX * scaleMat;
    FUG_SCENE.addEntity();
    FUG_SCENE.addComponent(ModelComponent({redPlasticMaterialResPtr, quadMeshResPtr}));
    FUG_SCENE.addComponent(std::move(floorTransform));
    TransformComponent plasticBallTransform;
    plasticBallTransform.transform << 1.f, 0.f, 0.f, -1.5f,
                                      0.f, 1.f, 0.f,  0.5f,
                                      0.f, 0.f, 1.f,   0.f,
                                      0.f, 0.f, 0.f,   1.f;
    FUG_SCENE.addEntity();
    FUG_SCENE.addComponent(ModelComponent({redPlasticMaterialResPtr, sphereMeshResPtr}));
    FUG_SCENE.addComponent(std::move(plasticBallTransform));
    TransformComponent ironBallTransform;
    ironBallTransform.transform << 1.f, 0.f, 0.f, 1.5f,
                                   0.f, 1.f, 0.f, 0.5f,
                                   0.f, 0.f, 1.f,  0.f,
                                   0.f, 0.f, 0.f,  1.f;
    FUG_SCENE.addEntity();
    FUG_SCENE.addComponent(ModelComponent({ironMaterialResPtr, sphereMeshResPtr}));
    FUG_SCENE.addComponent(std::move(ironBallTransform));

    // Set up camera movement
    bool cameraActive = false;
    Vector3Glf camPos(0.f, 0.f, -3.f);
    float camPitch = 0.f;
    float camYaw = 0.f;
    Matrix4Glf camPitchMat = Matrix4Glf::Identity();
    Matrix4Glf camYawMat = Matrix4Glf::Identity();
    Vector3Glf camFwd = Vector3Glf(0.f, 0.f, 1.f);
    float lastMouseX = sf::Mouse::getPosition().x;
    float lastMouseY = sf::Mouse::getPosition().y;

    Renderer renderer(camPos, Vector3Glf(0.f, 0.f, 1.f), Vector3Glf(0.f, 1.f, 0.f),
                      FOV, float(window->getSize().x) / window->getSize().y, Z_NEAR, Z_FAR);

    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                // end the program
                running = false;
            } else if (event.type == sf::Event::Resized) {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
                renderer._cam.projection(FOV, float(event.size.width) / event.size.height,
                                         Z_NEAR, Z_FAR);
                CENTER_X = event.size.width * 0.5;
                CENTER_Y = event.size.height * 0.5;
            } else if (cameraActive || !ImGui::IsMouseHoveringAnyWindow()) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    // Enable mouse control and hide cursor
                    cameraActive = !cameraActive;
                    sf::Mouse::setPosition({CENTER_X, CENTER_Y}, *window);
                }
            }
            ImGui_ImplSFMLGL3_HandleEvent(event);
        }

        // Update cam position
        if (cameraActive) {
            sf::Vector2i mPos = sf::Mouse::getPosition(*window);
            if (mPos.x != CENTER_X || mPos.y != CENTER_Y) {
                camYaw += float(mPos.x - CENTER_X) / window->getSize().x;
                camPitch += float(mPos.y - CENTER_Y) / window->getSize().y;
                // Limit pitch
                camPitch = std::min(std::max(camPitch, -MAX_PITCH), MAX_PITCH);
                // Calculate new fwd vector
                camPitchMat << 1.f,            0.f,             0.f, 0.f,
                                0.f, cosf(camPitch), -sinf(camPitch), 0.f,
                                0.f, sinf(camPitch),  cosf(camPitch), 0.f,
                                0.f,            0.f,             0.f, 1.f;
                camYawMat <<  cosf(camYaw), 0.f, sinf(camYaw), 0.f,
                                        0.f, 1.f,          0.f, 0.f,
                                -sinf(camYaw), 0.f, cosf(camYaw), 0.f,
                                        0.f, 0.f,          0.f, 1.f;
                Vector4Glf fwd = camYawMat * camPitchMat * Vector4Glf(0.f, 0.f, 1.f, 0.f);
                camFwd = Vector3Glf(fwd[0], fwd[1], fwd[2]);
                sf::Mouse::setPosition({CENTER_X, CENTER_Y}, *window);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            camPos += 0.05f * renderer._cam.getZAxis();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            camPos -= 0.05f * renderer._cam.getZAxis();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            camPos += 0.05f * renderer._cam.getXAxis();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            camPos -= 0.05f * renderer._cam.getXAxis();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            camPos += 0.05f * renderer._cam.getYAxis();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            camPos -= 0.05f * renderer._cam.getYAxis();
        renderer._cam.orient(camPos, camFwd, Vector3Glf(0.f, 1.f, 0.f));

        // Handle basic camera control
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
        FUG_SCENE.accept(renderer);

        ImGui::Render();
        // end the current frame (internally swaps the front and back buffers)
        window->display();
    }
    return 0;
}
