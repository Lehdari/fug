#version 330

// Inputs
layout(location = 0) in vec3 pos0;

// Homogenous corner vectors
uniform vec2 uCornerVecs[4];

void main()
{
    gl_Position = vec4(pos0, 1);
}
