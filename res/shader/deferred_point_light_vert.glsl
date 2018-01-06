#version 330

// Inputs
layout(location = 0) in vec3 pos0;

// Uniforms
uniform mat4 uModelToClip;

// Homogenous corner vectors
uniform vec2 uCornerVecs[4];

// Outputs
// Interpolated view ray direction
out vec2 rayDirVar;

void main()
{
    rayDirVar = uCornerVecs[gl_VertexID];
    gl_Position = uModelToClip * vec4(pos0, 1);
}
