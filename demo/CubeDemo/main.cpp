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
#include "Graphics/VertexData_Init_Text.hpp"

#include "Graphics/Canvas_SFML.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/SpriteRenderer.hpp"

#include "main.hpp"

int main()
{
    Canvas_SFML canvas;
    MeshComponent cubeMeshComp = loadCubeMeshComponent();
    TransformComponent transform;
    
    transform.transform << 1.f, 0.f, 0.f, 1.5f,
                           0.f, 1.f, 0.f, 1.f,
                           0.f, 0.f, 1.f, 1.f,
                           0.f, 0.f, 0.f,  1.f;

    Renderer renderer(Vector3Glf(0.f, 0.f, -3.f), Vector3Glf(0.f, 0.f, 1.f),
                      Vector3Glf(0.f, 1.f, 0.f), 90.f, 1280/720.f, 1.f, 10.f);


    bool is_running = true;
    auto& win = *canvas.getWindow();

    while (is_running) {
        
        // Handle window events
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // End the program
                is_running = false;
            }
            else if (event.type == sf::Event::Resized) {
                // Adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // Clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
        // Draw
        renderer(cubeMeshComp, transform);

        // End the current frame (internally swaps the front and back buffers)
        win.display();
    }
    return 0;
}
