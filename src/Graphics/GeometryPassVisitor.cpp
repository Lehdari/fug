#include "Graphics/GeometryPassVisitor.hpp"

using namespace fug;

GeometryPassVisitor::GeometryPassVisitor(const Camera& c) :
    _cam(c)
{
    glDepthMask(GL_TRUE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}

bool GeometryPassVisitor::operator()(MeshComponent& mesh, TransformComponent& transform) {
    mesh.draw(transform.transform, _cam.getView(), _cam.getProj());
    return true;
}
