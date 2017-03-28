#version 330

// Inputs
layout(location = 0) in vec3 pos0;
layout(location = 1) in vec2 tex0;
layout(location = 2) in vec3 norm0;

// Transformations
uniform mat4 uModelToClip;
uniform mat4 uModelToCam;
uniform mat4 uNormalToCam;

// Outputs
struct VertexAttr {
    vec3 pos;
    vec3 norm;
    vec2 tex;
};
out VertexAttr attrVar;

void main()
{
    attrVar.pos = (uModelToCam * vec4(pos0, 1)).xyz;
    attrVar.norm = (uNormalToCam * vec4(norm0, 0)).xyz;
    attrVar.tex = tex0;
    gl_Position  = uModelToClip * vec4(pos0, 1);
}
