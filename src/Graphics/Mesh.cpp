#include <Graphics/Mesh.hpp>

using namespace fug;


Mesh::Mesh(void) :
    _vertexArrayObjectId(0),
    _nIndices(0),
    _positionBufferId(0),
    _texCoordBufferId(0),
    _normalBufferId(0),
    _elementBufferId(0)
{}

void Mesh::draw(const Matrix4Glf& model, const Matrix4Glf& camera, const Matrix4Glf& proj) const
{
    
    _material->useMaterial(model, camera, proj);
    glBindVertexArray(_vertexArrayObjectId);

    glDrawElements(GL_TRIANGLES, _nIndices, GL_UNSIGNED_INT, (GLvoid*)0);

    glBindVertexArray(0);
}

ResourcePointer<Material> Mesh::getMaterialPointer(void) const
{
    return _material;
}
