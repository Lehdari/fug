#version 410

// Inputs
layout(location = 0) in vec3 pos0;
layout(location = 1) in vec3 norm0;
layout(location = 2) in vec2 tex0;

// Transformations
uniform mat4 uModelToClip;
uniform mat4 uModelToCam;

// Outputs
out vec3 posVar;
out vec3 normVar;
out vec2 texVar;

void main()
{
    posVar = (uModelToCam * vec4(pos0, 1)).xyz;
    normVar = norm0;
    texVar = tex0;
    gl_Position  = uModelToClip * vec4(pos0, 1);
}
