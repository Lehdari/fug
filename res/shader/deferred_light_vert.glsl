#version 330

layout (location = 0) in vec3 pos0;

void main()
{
    gl_Position = vec4(pos0, 1);
}
