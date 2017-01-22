#include <Graphics/VertexData.hpp>


using namespace fug;


VertexData::VertexData(void) :
    usingTexCoords_(false),
    usingNormals_(false),
    usingIndexing_(false)
{}

bool VertexData::usesTextureCoordinates(void) const {
    return usingTexCoords_;
}

bool VertexData::usesNormals(void) const {
    return usingNormals_;
}

bool VertexData::usesIndexing(void) const {
    return usingIndexing_;
}

const std::vector<std::array<float, 4>>& VertexData::getPositions(void) const {
    return positions_;
}

const std::vector<std::array<float, 3>>& VertexData::getTextureCoordinates(void) const {
    return texCoords_;
}

const std::vector<std::array<float, 3>>& VertexData::getNormals(void) const {
    return normals_;
}

const std::vector<unsigned>& VertexData::getIndices(void) const {
    return indices_;
}
