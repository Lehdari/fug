#include "Graphics/RenderObject.hpp"

using namespace fug;

void fug::renderObjects(std::vector<RenderObject>& objects, Camera& cam)
{
    for (auto& obj : objects) {
        // Bind shader
        glUseProgram(obj.shaderID);
        // Bind textures
        auto nValidBinds = std::min(obj.textures.size(), obj.uLocs_Sampler2D.size());
        for (auto i=0u; i<nValidBinds; ++i) {
            glActiveTexture(GL_TEXTURE0+i);
            glBindTexture(GL_TEXTURE_2D, obj.textures[i]);
            glUniform1i(obj.uLocs_Sampler2D[i], i);
        }
        // Bind uniforms
        Matrix4Glf modelToCam = cam.getView() * obj.transform;
        Matrix4Glf modelToClip = cam.getProj() * modelToCam;
        Matrix4Glf normalToCam = modelToCam.transpose().inverse();
        glUniformMatrix4fv(obj.uLocs_Mat4[0], 1, GL_FALSE, modelToClip.data());
        glUniformMatrix4fv(obj.uLocs_Mat4[1], 1, GL_FALSE, modelToCam.data());
        glUniformMatrix4fv(obj.uLocs_Mat4[2], 1, GL_FALSE, normalToCam.data());
        glUniform3fv(obj.uLocs_Vec3[0], 1, obj.specularColor.data());
        glUniform1f(obj.uLocs_Float[0], obj.specularExp);
        // Draw
        glBindVertexArray(obj.vao);
        glDrawElements(GL_TRIANGLES, obj.nIndices, GL_UNSIGNED_INT, (GLvoid*)0);
        glBindVertexArray(0);
    }
}
