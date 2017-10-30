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

const ResourcePointer<Material>& Mesh::getMaterialPointer(void) const
{
    return _material;
}

GLuint Mesh::getVAO() const
{
    return _vertexArrayObjectId;
}
uint32_t Mesh::getIndexCount() const
{
    return _nIndices;
}
