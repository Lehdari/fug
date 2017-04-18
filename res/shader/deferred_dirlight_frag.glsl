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

// Light uniforms
uniform vec3 uLightDir;
uniform vec3 uLightCol;
uniform float uDirectInt;
uniform float uAmbientInt;

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
        vec3 diffuseCol = texture(diffuseMap, mapCoord).rgb;
        vec3 specularCol = texture(specularMap, mapCoord).rgb;
        float specularExp = texture(specularMap, mapCoord).a;
        float linearDepth = texture(depthMap, mapCoord).r;

        // Lighting
        vec3 N = texture(normalMap, mapCoord).xyz;;
        float diffuseLight = max(0, dot(N, -uLightDir));

        float specularLight = 0;
        if (diffuseLight > 0) {
            vec3 V = normalize(vec3(-rayDirVar, 1));
            vec3 h = normalize(V + uLightDir);
            specularLight = pow(max(0, dot(N, h)), specularExp);
        }

        vec3 litCol = diffuseCol.xyz * (uAmbientInt +
                                        uDirectInt * diffuseLight +
                                        specularCol * specularLight);
        fragColor = vec4(litCol, 1);
    }
}
