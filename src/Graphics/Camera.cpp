#include "Graphics/Camera.hpp"


using namespace fug;

Camera::Camera(const Vector3Glf& position, const Vector3Glf& forward, const Vector3Glf& up,
               const float& fovX, const float& aspectRatio,
               const float& near, const float& far) :
    _fovX(fovX), _aspectRatio(aspectRatio), _near(near), _far(far)
{
    projection(fovX, aspectRatio, near, far);
    lookAt(position, forward, up);
}

Camera::Camera(const Camera& c)
{
    _xAxis = c._xAxis;
    _yAxis = c._yAxis;
    _zAxis = c._zAxis;
    _fovX = c._fovX;
    _aspectRatio = c._aspectRatio;
    _near = c._near;
    _far = c._far;
    _orientation = c._orientation;
    _projection = c._projection;
}

Camera& Camera::operator=(const Camera& other)
{
    if (this != &other) {
        this->_xAxis = other._xAxis;
        this->_yAxis = other._yAxis;
        this->_zAxis = other._zAxis;
        this->_fovX = other._fovX;
        this->_aspectRatio = other._aspectRatio;
        this->_near = other._near;
        this->_far = other._far;
        this->_orientation = other._orientation;
        this->_projection = other._projection;
    }
    return *this;
}

void Camera::lookAt(const Vector3Glf& from, const Vector3Glf& to, const Vector3Glf& up)
{
    // Precalc axis
    _zAxis = (to - from).normalized();
    _xAxis = up.cross(_zAxis).normalized();
    _yAxis = _zAxis.cross(_xAxis);

    // Camera looks at +z in it's own coordinate system
    _orientation << _xAxis[0], _xAxis[1], _xAxis[2], -_xAxis.dot(from),
                    _yAxis[0], _yAxis[1], _yAxis[2], -_yAxis.dot(from),
                    _zAxis[0], _zAxis[1], _zAxis[2], -_zAxis.dot(from),
                         0.f,      0.f,      0.f,              1.f;
}

void Camera::orient(const Vector3Glf& pos, const Vector3Glf& fwd, const Vector3Glf& up)
{
    // Precalc axis
    _zAxis = fwd.normalized();
    _xAxis = up.cross(_zAxis).normalized();
    _yAxis = _zAxis.cross(_xAxis);

    // Camera looks at +z in it's own coordinate system
    _orientation << _xAxis[0], _xAxis[1], _xAxis[2], -_xAxis.dot(pos),
                    _yAxis[0], _yAxis[1], _yAxis[2], -_yAxis.dot(pos),
                    _zAxis[0], _zAxis[1], _zAxis[2], -_zAxis.dot(pos),
                          0.f,       0.f,       0.f,              1.f;
}

void Camera::projection(const float& fovX, const float& aspectRatio,
                        const float& near,const float& far)
{
    // Update members
    _fovX = fovX;
    _aspectRatio = aspectRatio;
    _near = near;
    _far = far;

    // Precalc helpers
    float r = tanf(0.5f * fovX);
    float t = r / aspectRatio;
    float farmnear = far - near;

    // No need to flip z-axis like many sources do as we use left handed coordinate system
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

float Camera::getFovX(void) const
{
    return _fovX;
}

float Camera::getAspectRatio(void) const
{
    return _aspectRatio;
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
