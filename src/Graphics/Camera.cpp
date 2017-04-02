#include "Graphics/Camera.hpp"


using namespace fug;

Camera::Camera(const Vector3Glf& position, const Vector3Glf& forward, const Vector3Glf& up,
               const float& fov, const float& aspectRatio,
               const float& near, const float& far) :
    _position(position), _forward(forward), _up(up),
    _fov(fov), _aspectRatio(aspectRatio), _near(near), _far(far)
{
    projection(fov, aspectRatio, near, far);
    lookAt(position, forward, up);
}


void Camera::lookAt(const Vector3Glf& from, const Vector3Glf& to, const Vector3Glf& up)
{
    Vector3Glf xAxis, yAxis, zAxis;

    zAxis = (to - from).normalized();
    xAxis = up.cross(zAxis).normalized();
    yAxis = zAxis.cross(xAxis);

    _orientation << xAxis[0], xAxis[1], xAxis[2], -xAxis.dot(from),
                    yAxis[0], yAxis[1], yAxis[2], -yAxis.dot(from),
                    zAxis[0], zAxis[1], zAxis[2], -zAxis.dot(from),
                         0.f,      0.f,      0.f,              1.f;
}

void Camera::projection(const float& fov, const float& aspectRatio,
                        const float& near,const float& far)
{
    float r = tanf(fov / 2.0f);
    float t = r / aspectRatio;
    float farmnear = far - near;

    _projection << 1.f / r,     0.f,                     0.f,                          0.f,
                       0.f, 1.f / t,                     0.f,                          0.f,
                       0.f,     0.f, (far + near) / farmnear, -2.f * far * near / farmnear,
                       0.f,     0.f,                     1.f,                          0.f;
}

const Vector3Glf& Camera::getPosition(void) const
{
    return _position;
}

const Matrix4Glf Camera::getWorldToClip(void) const
{
    return _projection * _orientation;
}

const Matrix4Glf Camera::getView(void) const
{
    return  _orientation;
}

const Matrix4Glf Camera::getProj(void) const
{
    return _projection;
}
