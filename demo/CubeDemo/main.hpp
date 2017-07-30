
#include "Engine/ResourceLoader.hpp"
#include "Core/ResourceManager.hpp"
#include "Core/EventManager.hpp"
#include "Core/Scene.hpp"

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

#include "Core/MathTypes.hpp"

#include "Logic/MotionVisitor.hpp"
#include "Logic/TransformVisitor.hpp"

#include "ControlVisitor.hpp"
#include "BeatComponent.hpp"
#include "BeatVisitor.hpp"

#include <SFML/Audio.hpp>

using namespace fug;
