#ifndef FUG_GRAPHICS_SPRITERENDERER_HPP
#define FUG_GRAPHICS_SPRITERENDERER_HPP


#include <Core/MathTypes.hpp>
#include <Core/Visitor.hpp>
#include <Logic/TransformComponent.hpp>
#include <Graphics/SpriteMeshComponent.hpp>
#include <Graphics/Camera.hpp>

namespace fug {

    // NOTE: a second component here containing animation frame info!!
    class SpriteRenderer : public Visitor<SpriteRenderer, SpriteMeshComponent, TransformComponent>{
    public:
        SpriteRenderer(const Vector3Glf& position, const Vector3Glf& forward, const Vector3Glf& up,
                 const float& fov, const float& aspectRatio,
                 const float& near, const float& far);
        
        bool operator()(SpriteMeshComponent& sprite, TransformComponent& transform);
        
    private:
        Camera _cam;

    };

} // namespace fug


#endif // FUG_GRAPHICS_SPRITERENDERER_HPP
