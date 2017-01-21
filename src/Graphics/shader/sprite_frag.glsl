#version 330

// Textures
uniform sampler2D diffuseSampler;

// Interpolated inputs
in vec2 texVar;

out vec4 fragColor;

const float lightIntensity = 0.8;
const vec3 toLight = vec3(0, 0, -1);

void main()
{
    // Diffuse color
    vec3 diffuseCol = texture(diffuseSampler, texVar).xyz;
    
    sumCol += lightIntensity * diffuseCol;
    
    fragColor = vec4(sumCol, 1);
}
