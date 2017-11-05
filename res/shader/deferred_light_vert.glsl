#version 330

// Inputs
layout(location = 0) in vec3 pos0;

// Homogenous corner vectors
uniform vec2 uCornerVecs[4];

// Outputs
// Interpolated view ray direction
out vec2 rayDirVar;

void main()
{
    rayDirVar = uCornerVecs[gl_VertexID];
    gl_Position = vec4(pos0, 1);
}
