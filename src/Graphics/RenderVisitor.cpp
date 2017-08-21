#include "Graphics/RenderVisitor.hpp"
#include "Core/EventManager.hpp"

using namespace fug;

RenderVisitor::RenderVisitor() : _cam(nullptr)
{}

bool RenderVisitor::operator()(MeshComponent& mesh, TransformComponent& transform) {
    mesh.draw(transform.transform ,_cam->orientation, _cam->projection);
    return true;
}

bool RenderVisitor::initCamera() {
    for (auto& event : FUG_EVENT_MANAGER.template getMailbox<CameraComponent*>()) {
        _cam = event.data;
    }
    return bool(_cam);
}
