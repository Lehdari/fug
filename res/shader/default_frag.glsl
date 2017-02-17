#version 410

// Transformation
uniform mat4 uNormalToCam;

// Material
uniform vec3 uSpecularCol;
uniform float uSpecularExp;

// Textures
uniform sampler2D diffuseSampler;

// Interpolated inputs
in vec3 posVar;
in vec3 normVar;
in vec2 texVar;

out vec4 fragColor;

const float lightIntensity = 0.8f;
const vec3 toLight = vec3(0, 0, -1);

void main()
{
    // Diffuse color
    vec3 diffuseCol = texture(diffuseSampler, texVar).xyz;
    
    // Lighting
    vec3 sumCol = vec3(0);
    
    vec3 N = normalize((uNormalToCam * vec4(normVar, 0)).xyz);
    vec3 diffuse = diffuseCol.xyz * max(0, dot(N, toLight));
    
    vec3 V = -normalize(posVar);
    vec3 h = normalize(V + toLight);
    vec3 specular = uSpecularCol * pow(max(0, dot(N, h)), uSpecularExp);
    
    sumCol += lightIntensity * (diffuse + specular);
    
    fragColor = vec4(diffuseCol, 1);
}
