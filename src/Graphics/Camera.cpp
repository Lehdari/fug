#include "Graphics/Camera.hpp"


using namespace fug;

Camera::Camera(const Vector3Glf& position, const Vector3Glf& forward, const Vector3Glf& up,
               const float& fov, const float& aspectRatio,
               const float& near, const float& far) :
    _fov(fov), _aspectRatio(aspectRatio), _near(near), _far(far)
{
    projection(fov, aspectRatio, near, far);
    lookAt(position, forward, up);
}


void Camera::lookAt(const Vector3Glf& from, const Vector3Glf& to, const Vector3Glf& up)
{
    _zAxis = (to - from).normalized();
    _xAxis = up.cross(_zAxis).normalized();
    _yAxis = _zAxis.cross(_xAxis);

    _orientation << _xAxis[0], _xAxis[1], _xAxis[2], -_xAxis.dot(from),
                    _yAxis[0], _yAxis[1], _yAxis[2], -_yAxis.dot(from),
                    _zAxis[0], _zAxis[1], _zAxis[2], -_zAxis.dot(from),
                         0.f,      0.f,      0.f,              1.f;
}

void Camera::orient(const Vector3Glf& pos, const Vector3Glf& fwd, const Vector3Glf& up)
{
    _zAxis = fwd.normalized();
    _xAxis = up.cross(_zAxis).normalized();
    _yAxis = _zAxis.cross(_xAxis);

    _orientation << _xAxis[0], _xAxis[1], _xAxis[2], -_xAxis.dot(pos),
                    _yAxis[0], _yAxis[1], _yAxis[2], -_yAxis.dot(pos),
                    _zAxis[0], _zAxis[1], _zAxis[2], -_zAxis.dot(pos),
                          0.f,       0.f,       0.f,              1.f;
}

void Camera::projection(const float& fov, const float& aspectRatio,
                        const float& near,const float& far)
{
    float r = tanf(0.5f * fov);
    float t = r / aspectRatio;
    float farmnear = far - near;

    _projection << 1.f / r,     0.f,                     0.f,                          0.f,
                       0.f, 1.f / t,                     0.f,                          0.f,
                       0.f,     0.f, (far + near) / farmnear, -2.f * far * near / farmnear,
                       0.f,     0.f,                     1.f,                          0.f;
}

const Vector3Glf& Camera::getXAxis(void) const
{
    return _xAxis;
}

const Vector3Glf& Camera::getYAxis(void) const
{
    return _yAxis;
}

const Vector3Glf& Camera::getZAxis(void) const
{
    return _zAxis;
}

const Matrix4Glf Camera::getWorldToClip(void) const
{
    return _projection * _orientation;
}

const Matrix4Glf& Camera::getView(void) const
{
    return  _orientation;
}

const Matrix4Glf& Camera::getProj(void) const
{
    return _projection;
}
