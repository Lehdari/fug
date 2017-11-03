#include "Graphics/RenderingMatrixType.hpp"

#include <unordered_map>

using namespace fug;

namespace {

    const std::unordered_map<std::string, RenderingMatrixType> matrixTypesByString = {
        {"Model", RenderingMatrixType::Model},
        {"View", RenderingMatrixType::View},
        {"Projection", RenderingMatrixType::Projection},
        {"ModelToView", RenderingMatrixType::ModelToView},
        {"ModelToClip", RenderingMatrixType::ModelToClip},
        {"NormalToView", RenderingMatrixType::NormalToView}
    };

    const std::vector<GLint> initialMatrixLocations(static_cast<size_t>(RenderingMatrixType::TYPE_COUNT), -1);

}

RenderingMatrixType fug::getRenderingMatrixType(const std::string& s)
{
    return matrixTypesByString.at(s);
}

std::vector<GLint> fug::initRenderingMatrixLocations()
{
    return initialMatrixLocations;
}
