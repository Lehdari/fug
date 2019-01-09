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
layout (location = 0) out vec4 normalDepthOut;
layout (location = 1) out vec4 albedoOut;
layout (location = 2) out vec2 roughnessMetalnessOut;

void main()
{
    normalDepthOut = vec4(normalize(attrVar.norm), attrVar.pos.z);
    albedoOut = texture(albedoSampler, attrVar.tex);
    roughnessMetalnessOut = vec2(texture(roughnessSampler, attrVar.tex).r,
                                 texture(metalnessSampler,attrVar.tex));
}
