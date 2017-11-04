#version 330

// Textures
uniform sampler2D albedoSampler;
uniform sampler2D roughnessSampler;
uniform sampler2D metalnessSampler;

// Interpolated inputs
struct VertexAttr {
    vec3 pos;
    vec3 norm;
    vec2 tex;
};
in VertexAttr attrVar;
in vec3 toLight;

// Outputs
layout (location = 0) out float depthOut;
layout (location = 1) out vec3 normalOut;
layout (location = 2) out vec4 albedoOut;
layout (location = 3) out float roughnessOut;
layout (location = 4) out float metalnessOut;

void main()
{
    depthOut = attrVar.pos.z;
    normalOut = normalize(attrVar.norm);
    albedoOut = texture(albedoSampler, attrVar.tex);
    roughnessOut = texture(roughnessSampler, attrVar.tex).r;
    metalnessOut = texture(metalnessSampler, attrVar.tex).r;
}
