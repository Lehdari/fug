#include <Graphics/MeshComponent.hpp>


using namespace fug;


MeshComponent::MeshComponent(ResourcePointer<Mesh>& mesh) :
    mesh_(mesh)
{}

const ResourcePointer<Mesh>& MeshComponent::getMeshPointer(void) const {
    return mesh_;
}
