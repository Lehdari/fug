#ifndef FUG_GRAPHICS_MESHCOMPONENT_HPP
#define FUG_GRAPHICS_MESHCOMPONENT_HPP


#include "Graphics/Mesh.hpp"
#include "Core/MathTypes.hpp"


namespace fug {

    class MeshComponent {
    public:
        MeshComponent(ResourcePointer<Mesh>& mesh);

        const ResourcePointer<Mesh>& getMeshPointer(void) const;

    private:
        ResourcePointer<Mesh> mesh_;
    };

} // namespace fug


#endif // FUG_GRAPHICS_MESHCOMPONENT_HPP

