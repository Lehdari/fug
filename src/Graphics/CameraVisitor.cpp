#include "Graphics/CameraVisitor.hpp"
#include "Core/EventManager.hpp"

using namespace fug;

bool CameraVisitor::operator()(CameraComponent& cam, TransformComponent& trans) {
    FUG_EVENT_MANAGER.pushEvent(&cam);
    orientation(cam, trans);
    projection(cam);
    return true;
}

void CameraVisitor::orientation(CameraComponent& cam, TransformComponent& trans) {
    static Vector3Glf up = {0,1,0};
    Vector3Glf xAxis, yAxis, zAxis;

    zAxis = trans.orientation.vec().normalized();
    xAxis = up.cross(zAxis).normalized();
    yAxis = zAxis.cross(xAxis);

    cam.orientation << xAxis[0], xAxis[1], xAxis[2], -xAxis.dot(trans.position),
                       yAxis[0], yAxis[1], yAxis[2], -yAxis.dot(trans.position),
                       zAxis[0], zAxis[1], zAxis[2], -zAxis.dot(trans.position),
                       0.f,      0.f,      0.f,      1.f;
}

void CameraVisitor::projection(CameraComponent& cam) {
    float r = tanf(cam.fov / 2.0f);
    float d = cam.far - cam.near;

    cam.projection << 1.f / r, 0.f,                  0.f,                      0.f,
                      0.f,     cam.aspect_ratio / r, 0.f,                      0.f,
                      0.f,     0.f,                  (cam.far + cam.near) / d, 2.f * cam.far * cam.near / -d,
                      0.f,     0.f,                  1.f,                      0.f;
}

