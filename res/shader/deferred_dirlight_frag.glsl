#version 330

// GBuffer
uniform sampler2D depthMap;
uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;

// Control booleans
uniform bool uOnlyDepth;
uniform bool uOnlyDiffuse;
uniform bool uOnlyNormal;
uniform bool uOnlySpecular;

// Input
in vec2 rayDirVar;

// Output
out vec4 fragColor;

// TODO: Pass from cpu
const vec2 viewport = vec2(1280, 720);
const float far = 10.0;

void main()
{
    vec2 mapCoord = gl_FragCoord.xy / viewport;

    if (uOnlyDepth)
        fragColor = vec4(vec3(texture(depthMap, mapCoord).r / far) , 1);
    else if (uOnlyDiffuse)
        fragColor = texture(diffuseMap, mapCoord);
    else if (uOnlyNormal)
        fragColor = vec4(texture(normalMap, mapCoord).xyz, 1);
    else if (uOnlySpecular)
        fragColor = texture(specularMap, mapCoord);
    else {
        fragColor = vec4(-rayDirVar, 0, 1);
    }
}
