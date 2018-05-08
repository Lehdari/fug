#version 330

// Inputs
layout(location = 0) in vec3 pos0;

// Uniforms
uniform mat4 uModelToClip;

void main()
{
    gl_Position = uModelToClip * vec4(pos0, 1);
}
