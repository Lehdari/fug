#include <Graphics/Renderer.hpp>


using namespace fug;

Renderer::Renderer(const Vector3Glf& position, const Vector3Glf& forward, const Vector3Glf& up,
                   const float& fov, const float& aspectRatio,
                   const float& near, const float& far) :
    _position(position), _forward(forward), _up(up),
    _fov(fov), _aspectRatio(aspectRatio), _near(near), _far(far)
{
    projection(fov, aspectRatio, near, far);
    lookAt(position, forward, up);
}

bool Renderer::operator()(SpriteMeshComponent& component) {
    component.draw(_projection * _orientation, 0, 0);
    return true;
}

void Renderer::lookAt(const Vector3Glf& from, const Vector3Glf& to, const Vector3Glf& up) {
    Vector3Glf xAxis, yAxis, zAxis;

    zAxis = (to - from).normalized();
    xAxis = up.cross(zAxis).normalized();
    yAxis = zAxis.cross(xAxis);

    _orientation <<  xAxis[0] ,  xAxis[1] ,  xAxis[2] , -xAxis.dot(from) ,
                     yAxis[0] ,  yAxis[1] ,  yAxis[2] , -yAxis.dot(from) ,
                    -zAxis[0] , -zAxis[1] , -zAxis[2] ,  zAxis.dot(from) ,
                         0.0f ,      0.0f ,      0.0f ,             1.0f ;
}

void Renderer::projection(const float& fov, const float& aspectRatio,
                        const float& near,const float& far) {
    float r = tanf(fov / 2.0f) * near;
    float t = r / aspectRatio;

    _projection << near/r ,   0.0f ,                   0.0f ,                      0.0f ,
                     0.0f , near/t ,                   0.0f ,                      0.0f ,
                     0.0f ,   0.0f , -(far+near)/(far-near) , -2.0f*far*near/(far-near) ,
                     0.0f ,   0.0f ,                  -1.0f ,                      0.0f ;
}

const Vector3Glf& Renderer::getPosition(void) const {
    return _position;
}
