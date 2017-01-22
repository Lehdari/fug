#include <Graphics/MeshComponent.hpp>


using namespace fug;


MeshComponent::MeshComponent(ResourcePointer<Mesh>& mesh,
                             const Matrix4Glf& transformation) :
    mesh_(mesh),
    transformation_(transformation)
{}

const Mesh& MeshComponent::getMesh(void) const {
    return *mesh_;
}

ResourcePointer<Mesh> MeshComponent::getMeshPointer(void) const {
    return mesh_;
}

void MeshComponent::setTransformation(const Matrix4Glf& transformation) {
    transformation_ = transformation;
}

void MeshComponent::draw(const Matrix4Glf& view, const Matrix4Glf& proj) const {
    mesh_->draw(transformation_, view, proj);
}
