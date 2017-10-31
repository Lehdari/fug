#ifndef FUG_GRAPHICS_MODELCOMPONENT_HPP
#define FUG_GRAPHICS_MODELCOMPONENT_HPP

#include "Graphics/Material.hpp"
#include "Graphics/Mesh.hpp"
#include "Core/MathTypes.hpp"

namespace fug {

    struct ModelComponent {
        ResourcePointer<Material> material;
        ResourcePointer<Mesh> mesh;
    };

} // namespace fug

#endif // FUG_GRAPHICS_MODELCOMPONENT_HPP
