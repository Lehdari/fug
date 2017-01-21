#version 330

// Inputs
layout(location = 0) in vec3 pos0;

// Transformations
uniform mat4 uModelToClip;

// Animation uniforms
uniform float uSpriteW;
uniform float uSpriteH;
uniform int   uFrameRow;
uniform int   uFrameColumn;

// Outputs
out vec2 texVar;

void main()
{
    texVar.x  = (pos0.x == 1.0) ? uFrameColumn * uSpriteW : (uFrameColumn + 1) * uSpriteW;
    texVar.y  = (pos0.y == 1.0) ? 1 - uFrameRow * uSpriteH : 1 - (uFrameRow + 1) * uSpriteH;
    gl_Position  = uModelToClip * vec4(pos0, 1);
}
