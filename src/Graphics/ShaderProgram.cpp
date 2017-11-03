#include "Graphics/ShaderProgram.hpp"

using namespace fug;

ShaderProgram::ShaderProgram(void) :
    programId_(0)
{ }

GLuint ShaderProgram::getId(void) const {
    return programId_;
}

const std::vector<GLint>& ShaderProgram::getMatrixLocations() const
{
    return _matrixLocations;
}
