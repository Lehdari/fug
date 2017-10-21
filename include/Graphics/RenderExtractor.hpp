#ifndef FUG_GRAPHICS_RENDEREXTRACTOR_HPP
#define FUG_GRAPHICS_RENDEREXTRACTOR_HPP


#include "Core/MathTypes.hpp"
#include "Core/Visitor.hpp"
#include "Logic/TransformComponent.hpp"
#include "Graphics/MeshComponent.hpp"
#include "Graphics/RenderObject.hpp"

namespace fug {

    // NOTE: a second component here containing animation frame info!!
    class RenderExtractor : public Visitor<RenderExtractor, MeshComponent, TransformComponent>{
    public:
        RenderExtractor(std::vector<RenderObject>& objects);

        bool operator()(MeshComponent& mesh, TransformComponent& transform);

    private:
        std::vector<RenderObject>& _objects;

    };

} // namespace fug


#endif // FUG_GRAPHICS_RENDEREXTRACTOR_HPP
