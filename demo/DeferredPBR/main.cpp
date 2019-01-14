#include "imgui-fug/imgui/imgui.h"
#include "imgui-fug/imgui_impl_sfml_gl3.h"

#include "Core/ResourceManager.hpp"
#include "Core/Binary.hpp"
#include "Core/Binary_Init_File.hpp"
#include "Core/Scene.hpp"
#include "Core/Text.hpp"
#include "Core/Text_Init_File.hpp"

#include "Engine/ResourceLoader.hpp"

#include "Graphics/GBuffer.hpp"
#include "Graphics/PointLightPass.hpp"
#include "Graphics/DirectionalLightPass.hpp"
#include "Graphics/LightShaderBinding.hpp"
#include "Graphics/LightShaderBinding_Init.hpp"
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

using namespace fug;

namespace {
    const float FOV = 90.f * PI / 180.f;
    const float Z_NEAR = 0.1f;
    const float Z_FAR = 100.f;
    const float MAX_PITCH = PI * 0.4999f;
    int RES_X = 1280;
    int RES_Y = 720;
    int CENTER_X = RES_X * 0.5;
    int CENTER_Y = RES_Y * 0.5;

    float randf()
    {
        float per_half = 2.f / RAND_MAX;
        return rand() * per_half - 1.f;
    }
}

int main(void)
{
    Canvas_SFML c;
    sf::Window* window = c.getWindow();

    ImGui_ImplSFMLGL3_Init(window);

    // Load resources
    ResourceLoader resourceLoader("deferred_pbr.stfu");
    resourceLoader.load();

    auto ironMaterialResPtr = FUG_RESOURCE_MANAGER.getResource<Material>(FUG_RESOURCE_ID_MAP.getId("material_iron"));
    auto copperMaterialResPtr = FUG_RESOURCE_MANAGER.getResource<Material>(FUG_RESOURCE_ID_MAP.getId("material_copper"));
    auto redPlasticMaterialResPtr = FUG_RESOURCE_MANAGER.getResource<Material>(FUG_RESOURCE_ID_MAP.getId("material_red_plastic"));
    auto chalkMaterialResPtr = FUG_RESOURCE_MANAGER.getResource<Material>(FUG_RESOURCE_ID_MAP.getId("material_chalk"));

    auto sphereMeshResPtr = FUG_RESOURCE_MANAGER.getResource<Mesh>(FUG_RESOURCE_ID_MAP.getId("mesh_uvsphere"));
    auto quadMeshResPtr = FUG_RESOURCE_MANAGER.getResource<Mesh>(FUG_RESOURCE_ID_MAP.getId("mesh_quad"));
    auto bunnyMeshResPtr = FUG_RESOURCE_MANAGER.getResource<Mesh>(FUG_RESOURCE_ID_MAP.getId("mesh_bunny"));

    auto dirLightBindResPtr = FUG_RESOURCE_MANAGER.getResource<LightShaderBinding>(FUG_RESOURCE_ID_MAP.getId("light_shader_binding_directional"));
    auto pointLightBindResPtr = FUG_RESOURCE_MANAGER.getResource<LightShaderBinding>(FUG_RESOURCE_ID_MAP.getId("light_shader_binding_point"));

    auto stencilProgResPtr = FUG_RESOURCE_MANAGER.getResource<ShaderProgram>(FUG_RESOURCE_ID_MAP.getId("shaderprogram_stencil"));

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
    FUG_SCENE.addComponent(ModelComponent({chalkMaterialResPtr, quadMeshResPtr}));
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

    // Generate bunnyfield
    for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < 4; ++i) {
            TransformComponent bunnyTransform;
            bunnyTransform.transform << 2.f, 0.f, 0.f, -2.f + i * 1,
                                        0.f, 2.f, 0.f,         -1.f,
                                        0.f, 0.f, 2.f, -6.f + j * 1,
                                        0.f, 0.f, 0.f,          1.f;
            FUG_SCENE.addEntity();
            FUG_SCENE.addComponent(ModelComponent({chalkMaterialResPtr, bunnyMeshResPtr}));
            FUG_SCENE.addComponent(std::move(bunnyTransform));
        }
    }

    FUG_SCENE.addEntity();
    FUG_SCENE.addComponent(DirectionalLightComponent({ dirLightBindResPtr,
                                                       Vector3Glf(-0.5, -0.5, 1).normalized(),
                                                       { 1.0, 1.0, 1.0 }, { 0.05, 0.05, 0.05 }}));

    // Calculate light effect distance
    for (int i = 0; i < 10 ; i++) {
        Vector3Glf lInt(randf() * 0.5 + 1.f, randf() * 0.5 + 1.f, randf() * 0.5 + 1.f);
        Vector3Glf lAtten(0, 0, 1);
        float maxComp = fmax(fmax(lInt[0], lInt[1]), lInt[2]);
        lInt *= 0.7;
        // Limit for stencil at light values greater than 5/256
        float d = (-lAtten[1] + sqrt(lAtten[1] * lAtten[1] - 4 * lAtten[2] * (lAtten[0] - (256.f / 5) * maxComp))) / (2 * lAtten[2]);
        TransformComponent pointTransform;
        pointTransform.position = Vector3Glf(randf(), 0.1 * randf(), randf());
        pointTransform.position *= 3;
        pointTransform.position += Vector3Glf(-0.5f, 0.4f, -5.f);
        translation << 1.f, 0.f, 0.f, pointTransform.position[0],
                       0.f, 1.f, 0.f, pointTransform.position[1],
                       0.f, 0.f, 1.f, pointTransform.position[2],
                       0.f, 0.f, 0.f,                        1.f;
        Matrix4Glf scale;
        scale <<   d, 0.f, 0.f, 0.f,
                 0.f,   d, 0.f, 0.f,
                 0.f, 0.f,   d, 0.f,
                 0.f, 0.f, 0.f, 1.f;
        pointTransform.transform = translation * scale;
        FUG_SCENE.addEntity();
        FUG_SCENE.addComponent(PointLightComponent({ pointLightBindResPtr, sphereMeshResPtr, lInt, lAtten}));
        FUG_SCENE.addComponent(std::move(pointTransform));
    }

    // Set up camera movement
    bool cameraActive = false;
    Vector3Glf camPos(0.f, 0.f, -10.f);
    float camPitch = 0.f;
    float camYaw = 0.f;
    Matrix4Glf camPitchMat = Matrix4Glf::Identity();
    Matrix4Glf camYawMat = Matrix4Glf::Identity();
    Vector3Glf camFwd = Vector3Glf(0.f, 0.f, 1.f);
    float lastMouseX = sf::Mouse::getPosition().x;
    float lastMouseY = sf::Mouse::getPosition().y;

    // Rendering control
    int currentMode = 0;
    const char* renderModes[] = { "Shaded", "Normals + Depth", "Albedo", "Roughness + Metalness"};

    Renderer renderer(camPos, Vector3Glf(0.f, 0.f, 1.f), Vector3Glf(0.f, 1.f, 0.f),
                      FOV, float(window->getSize().x) / window->getSize().y, Z_NEAR, Z_FAR);
    Matrix4Glf normalToView = renderer._cam.getView().transpose().inverse();
    DirectionalLightPass dirLightPass(quadMeshResPtr, normalToView, renderer._cam.getFovX(), { RES_X, RES_Y });

    // Create gbuffer with normal+depth, albedo and roughness+metalness render targets
    auto gBuffer = std::shared_ptr<GBuffer>(new GBuffer(RES_X, RES_Y,
                                                        {GL_RGBA32F, GL_RGBA16, GL_RG8},
                                                        {   GL_RGBA,   GL_RGBA,  GL_RG} ));

    PointLightPass pointLightPass(renderer._cam, gBuffer, { RES_X, RES_Y }, stencilProgResPtr);

    bool running = true;
    while (running)
    {
        // Handle events
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                // End the program on esc
                running = false;
            } else if (event.type == sf::Event::Resized) {
                // update statics
                RES_X = event.size.width;
                RES_Y = event.size.height;
                CENTER_X = RES_X * 0.5;
                CENTER_Y = RES_Y * 0.5;
                // Adjust the viewport
                glViewport(0, 0, RES_X, RES_Y);
                // TODO: have viewport as a global?
                dirLightPass._viewportSize = { RES_X, RES_Y };
                pointLightPass._viewportSize = { RES_X, RES_Y };
                // Recalculate projection
                renderer._cam.projection(FOV, float(RES_X) / RES_Y, Z_NEAR, Z_FAR);
                // Resize rendering buffers
                gBuffer->resize(RES_X, RES_Y);
            } else if (cameraActive || !ImGui::IsMouseHoveringAnyWindow()) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    // Enable mouse control and hide cursor
                    cameraActive = !cameraActive;
                    window->setMouseCursorVisible(!cameraActive);
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
                // Recenter mouse
                sf::Mouse::setPosition({CENTER_X, CENTER_Y}, *window);
            }
        }
        // Update camera position if movement key(s) are pressed
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            camPos -= 0.05f * renderer._cam.getYAxis();
        // Reorient camera
        renderer._cam.orient(camPos, camFwd, Vector3Glf(0.f, 1.f, 0.f));
        dirLightPass._normalToView = renderer._cam.getView().transpose().inverse();
        dirLightPass._fovX = renderer._cam.getFovX();
        pointLightPass._cam = renderer._cam;

        // Handle basic camera control
        // Simple imgui-window
        ImGui_ImplSFMLGL3_NewFrame();
        // mousepos could be passed to imgui before event-handling and check this
        // to not pass mouse-events to program if hovering
        {
            ImGui::ListBox("", &currentMode, renderModes, 4, 4);
            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        // Clear final image
        gBuffer->clearFinal();

        // Draw geometry to gbuffer
        gBuffer->bindGeometryPass();
        glDepthMask(GL_TRUE);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
        FUG_SCENE.accept(renderer);
        glDepthMask(GL_FALSE);

        // Render contributions of point lights
        glEnable(GL_STENCIL_TEST);
        FUG_SCENE.accept(pointLightPass);
        glDisable(GL_STENCIL_TEST);

        // Render contributions of directional lights
        gBuffer->bindLightPass();
        dirLightPass.initPass();
        FUG_SCENE.accept(dirLightPass);

        // Select buffer to blit
        if (currentMode == 0) {
            // Default is to blit the complete frame
            gBuffer->bindFinalRead();
        } else {
            // Otherwise select from GBuffer in order
            gBuffer->bindRead(currentMode - 1);
        }

        // Blit selected buffer to screen
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(0, 0, RES_X, RES_Y, 0, 0, RES_X, RES_Y, GL_COLOR_BUFFER_BIT, GL_LINEAR);

        // Render GUI
        ImGui::Render();

        // End the current frame (internally swaps the front and back buffers)
        window->display();
    }
    return 0;
}
