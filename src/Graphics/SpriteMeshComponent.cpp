#include <Graphics/SpriteMeshComponent.hpp>

using namespace fug;


SpriteMeshComponent::SpriteMeshComponent(ResourcePointer<SpriteMesh>& mesh,
                                         const Matrix4Glf& transformation) :
    _mesh(mesh),
    _transformation(transformation)
{}

const SpriteMesh& SpriteMeshComponent::getMesh(void) const
{
    return *_mesh;
}

ResourcePointer<SpriteMesh> SpriteMeshComponent::getMeshPointer(void) const
{
    return _mesh;
}

void SpriteMeshComponent::setTransformation(const Matrix4Glf& transformation)
{
    _transformation = transformation;
}

void SpriteMeshComponent::draw(const Matrix4Glf& camera,
                               const GLint& frameRow, const GLint& frameColumn) const
{
    _mesh->draw(_transformation, camera, frameRow, frameColumn);
}
