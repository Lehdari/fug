#version 330

layout (location = 0) in vec3 pos0;

uniform vec2 uCornerVecs[4];

out vec2 rayDirVar;

void main()
{
    rayDirVar = uCornerVecs[gl_VertexID];
    gl_Position = vec4(pos0, 1);
}
