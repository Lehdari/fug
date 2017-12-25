#ifndef FUG_GRAPHICS_CAMERA_HPP
#define FUG_GRAPHICS_CAMERA_HPP


#include "Core/MathTypes.hpp"
#include "Core/Macros.hpp"


namespace fug {

    class Camera
    {
    public:
        Camera(const Vector3Glf& position, const Vector3Glf& forward, const Vector3Glf& up,
               const float& fov, const float& aspectRatio,
               const float& near, const float& far);
        Camera(const Camera& c);

        void lookAt(const Vector3Glf& from, const Vector3Glf& to, const Vector3Glf& up);
        void orient(const Vector3Glf& pos, const Vector3Glf& fwd, const Vector3Glf& up);
        void projection(const float& fov, const float& aspectRatio,
                        const float& near, const float& far);

        const Vector3Glf& getXAxis(void) const;
        const Vector3Glf& getYAxis(void) const;
        const Vector3Glf& getZAxis(void) const;

        const Matrix4Glf getWorldToClip(void) const;
        const Matrix4Glf& getView(void) const;
        const Matrix4Glf& getProj(void) const;

    private:
        // Orientation vectors
        Vector3Glf _xAxis;
        Vector3Glf _yAxis;
        Vector3Glf _zAxis;

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


#endif // FUG_GRAPHICS_CAMERA_HPP
