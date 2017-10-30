#include <Graphics/SpriteMesh.hpp>

using namespace fug;


SpriteMesh::SpriteMesh(void) :
    _vertexArrayObjectId(0),
    _nIndices(0),
    _positionBufferId(0),
    _elementBufferId(0)
{}

void SpriteMesh::draw(const Matrix4Glf& mvp, const GLint& frameRow, const GLint& frameColumn) const
{
    _material->useMaterial(mvp, frameRow, frameColumn);
    
    glBindVertexArray(_vertexArrayObjectId);

    // TODO_IMPLEMENT: draw arrays if not using indexing
    glDrawElements(GL_TRIANGLES, _nIndices, GL_UNSIGNED_INT, (GLvoid*)0);

    glBindVertexArray(0);
}

void SpriteMesh::draw(const Matrix4Glf& model, const Matrix4Glf& camera,
                      const GLint& frameRow, const GLint& frameColumn) const
{
    
    _material->useMaterial(model, camera, frameRow, frameColumn);
    glBindVertexArray(_vertexArrayObjectId);

    glDrawElements(GL_TRIANGLES, _nIndices, GL_UNSIGNED_INT, (GLvoid*)0); // TODO_IMPLEMENT: draw arrays if not using indexing

    glBindVertexArray(0);
}

ResourcePointer<SpriteMaterial> SpriteMesh::getMaterialPointer(void) const
{
    return _material;
}
