#include "Graphics/RenderExtractor.hpp"


using namespace fug;


RenderExtractor::RenderExtractor(std::vector<RenderObject>& objects) :
    _objects(objects)
{
}

bool RenderExtractor::operator()(MeshComponent& mesh, TransformComponent& transform) {
    RenderObject obj;
    obj.vao = mesh.getMesh()._vertexArrayObjectId;
    obj.nIndices = mesh.getMesh()._nIndices;
    for (auto& t : mesh.getMesh().getMaterial()._textures)
        obj.textures.emplace_back(t->textureId_);
    obj.shaderID = mesh.getMesh().getMaterial().getShaderId();
    obj.uLocs_Sampler2D = mesh.getMesh().getMaterial()._uniformLocations_Sampler2D;
    obj.uLocs_Float = mesh.getMesh().getMaterial()._uniformLocations_Float;
    obj.uLocs_Mat4 = mesh.getMesh().getMaterial()._uniformLocations_Mat4;
    obj.uLocs_Vec3 = mesh.getMesh().getMaterial()._uniformLocations_Vec3;
    obj.transform = transform.transform;
    obj.specularColor = mesh.getMesh().getMaterial()._specularColor;
    obj.specularExp = mesh.getMesh().getMaterial()._specularExp;
    _objects.emplace_back(std::move(obj));
    return true;
}
