#include <Graphics/SpriteMeshComponent.hpp>

using namespace fug;


SpriteMeshComponent::SpriteMeshComponent(ResourcePointer<SpriteMesh>& mesh) :
    _mesh(mesh)
{}

const SpriteMesh& SpriteMeshComponent::getMesh(void) const
{
    return *_mesh;
}

ResourcePointer<SpriteMesh> SpriteMeshComponent::getMeshPointer(void) const
{
    return _mesh;
}

void SpriteMeshComponent::draw(const Matrix4Glf& transform, const Matrix4Glf& camera,
                               const GLint& frameRow, const GLint& frameColumn) const
{
    _mesh->draw(transform, camera, frameRow, frameColumn);
}
