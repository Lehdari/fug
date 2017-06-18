#version 330

// GBuffer
uniform sampler2D depthMap;
uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;

// Light uniforms
uniform vec3 uLightPos;
uniform vec3 uLightCol;
uniform float uDirectInt;
uniform float uAttenConst;
uniform float uAttenLin;
uniform float uAttenExp;

// Input
in vec2 rayDirVar;

// Output
out vec4 fragColor;

// TODO: Pass from cpu
const vec2 viewport = vec2(1280, 720);

void main()
{
    vec2 mapCoord = gl_FragCoord.xy / viewport;

    vec3 diffuseCol = texture(diffuseMap, mapCoord).rgb;
    vec3 specularCol = texture(specularMap, mapCoord).rgb;
    float specularExp = texture(specularMap, mapCoord).a;
    float linearDepth = texture(depthMap, mapCoord).r;

    vec3 V = normalize(vec3(rayDirVar, 1));
    vec3 hitPos = V * linearDepth;
    vec3 hitToLight = uLightPos - hitPos;
    float lightDist = length(hitToLight);
    vec3 nHitToLight= hitToLight / lightDist;

    // Lighting
    vec3 N = texture(normalMap, mapCoord).xyz;;
    float diffuseLight = max(0, dot(N, nHitToLight));

    float specularLight = 0;
    if (diffuseLight > 0) {
        vec3 h = normalize(V + nHitToLight);
        specularLight = pow(max(0, dot(N, h)), specularExp);
    }

    vec3 col = diffuseCol.xyz * (uDirectInt * diffuseLight + specularCol * specularLight) * uLightCol;
    float atten = max(1, uAttenConst + uAttenLin * lightDist + uAttenExp * lightDist * lightDist);
    vec3 litCol = col / atten;
    fragColor = vec4(litCol, 1);
}
