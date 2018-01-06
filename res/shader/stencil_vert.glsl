#version 330

// Inputs
layout(location = 0) in vec3 pos0;
layout(location = 1) in vec2 tex0;
layout(location = 2) in vec3 norm0;

// Transformations
uniform mat4 uModelToClip;

void main()
{
    gl_Position  = uModelToClip * vec4(pos0, 1);
}
