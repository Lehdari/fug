#include "Graphics/ShaderObject.hpp"

using namespace fug;

ShaderObject::ShaderObject(void) :
    objectId_(0)
{ }

GLuint ShaderObject::getId(void) const {
    return objectId_;
}
