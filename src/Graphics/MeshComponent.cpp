#include <Graphics/MeshComponent.hpp>


using namespace fug;


MeshComponent::MeshComponent(ResourcePointer<Mesh>& mesh) :
    mesh_(mesh)
{}

const Mesh& MeshComponent::getMesh(void) const {
    return *mesh_;
}

ResourcePointer<Mesh> MeshComponent::getMeshPointer(void) const {
    return mesh_;
}

void MeshComponent::draw(const Matrix4Glf& transform, const Matrix4Glf& view, const Matrix4Glf& proj) const {
    mesh_->draw(transform, view, proj);
}
