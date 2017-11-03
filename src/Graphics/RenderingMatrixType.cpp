#include "Graphics/RenderingMatrixType.hpp"

#include <unordered_map>

#include "Core/Log.hpp"

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

RenderingMatrixType fug::getRenderingMatrixType(const std::string& matrixType)
{
    auto it = matrixTypesByString.find(matrixType);
    if (it != matrixTypesByString.end()) {
        return it->second;
    } else {
        FUG_LOG(LogLevel::Error)("RenderingMatrixType: invalid matrix type '%s'\n", matrixType.c_str());
        throw;
    }
}

std::vector<GLint> fug::initRenderingMatrixLocations()
{
    return initialMatrixLocations;
}
