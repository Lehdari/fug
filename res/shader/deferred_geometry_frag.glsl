#version 330

// Material
uniform vec3 uSpecularCol;
uniform float uSpecularExp;

// Textures
uniform sampler2D diffuseSampler;

// Interpolated input
struct VertexAttr {
    vec3 pos;
    vec3 norm;
    vec2 tex;
};
in VertexAttr attrVar;

layout (location = 0) out float depthOut;
layout (location = 1) out vec4 diffuseOut;
layout (location = 2) out vec3 normalOut;
layout (location = 3) out vec4 specularOut;

void main()
{
    depthOut = attrVar.pos.z;
    diffuseOut = texture(diffuseSampler, attrVar.tex);
    normalOut = normalize(attrVar.norm);
    specularOut.xyz = uSpecularCol;
    specularOut.w = uSpecularExp;
}
