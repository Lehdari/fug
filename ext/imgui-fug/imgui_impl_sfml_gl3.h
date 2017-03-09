// ImGui SFML binding with OpenGL3 + shaders
// In this binding, ImTextureID is used to store an OpenGL 'GLuint' texture identifier. Read the FAQ about ImTextureID in imgui.cpp.

// You can copy and use unmodified imgui_impl_* files in your project. See main.cpp for an example of using this.
// If you use this binding you'll need to call 4 functions: ImGui_ImplXXXX_Init(), ImGui_ImplXXXX_NewFrame(), ImGui::Render() and ImGui_ImplXXXX_Shutdown().
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

// Modified from imgui's example imgui_impl_glfw_gl3.h

#include "SFML/Window.hpp"

IMGUI_API bool        ImGui_ImplSFMLGL3_Init(sf::Window* window);
IMGUI_API void        ImGui_ImplSFMLGL3_Shutdown();
IMGUI_API void        ImGui_ImplSFMLGL3_NewFrame();
void                  ImGui_ImplSFMLGL3_HandleEvent(const sf::Event& e);

// Use if you want to reset your rendering device without losing ImGui state.
IMGUI_API void        ImGui_ImplSFMLGL3_InvalidateDeviceObjects();
IMGUI_API bool        ImGui_ImplSFMLGL3_CreateDeviceObjects();
