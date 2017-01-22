#ifndef FUG_GRAPHICS_RENDERER_HPP
#define FUG_GRAPHICS_RENDERER_HPP


#include <Core/Visitor.hpp>
#include <Graphics/SpriteMeshComponent.hpp>
#include <Core/MathTypes.hpp>

#include <stack>


namespace fug {

    // NOTE: a second component here containing animation frame info!!
    class Renderer : public Visitor<Renderer, SpriteMeshComponent>{
    public:
        Renderer(const Vector3Glf& position, const Vector3Glf& forward, const Vector3Glf& up,
                 const float& fov, const float& aspectRatio,
                 const float& near, const float& far);
        
        bool operator()(SpriteMeshComponent& component);
        
        void lookAt(const Vector3Glf& from, const Vector3Glf& to, const Vector3Glf& up);
        void projection(const float& fov, const float& aspectRatio,
                        const float& near,const float& far);

        const Vector3Glf& getPosition(void) const;
    
    private:
        //  Vectors for orientation matrix
        Vector3Glf _position;
        Vector3Glf _forward;
        Vector3Glf _up;

        //  Values for projection matrix
        float _fov;
        float _aspectRatio;
        float _near;
        float _far;

        //  Quaternion and matrices calculated from members above
        Matrix4Glf _orientation;
        Matrix4Glf _projection;

    };

} // namespace fug


#endif // FUG_GRAPHICS_BASICCAMERA_HPP
