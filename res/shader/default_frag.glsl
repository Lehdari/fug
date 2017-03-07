#version 330

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

const vec3 ambientLight = vec3(0.2, 0.2, 0.2);
const float dirLightIntensity = 0.8f;
const vec3 toLightCam = normalize(vec3(0, 0, -1));

void main()
{
    // Diffuse color
    vec3 diffuseCol = texture(diffuseSampler, texVar).xyz;

    // Lighting
    vec3 N = normalize(normVar);
    float diffuseLight = max(0, dot(N, toLightCam));

    float specularLight = 0;
    if (diffuseLight > 0) {
        vec3 V = -normalize(posVar);
        vec3 h = normalize(V + toLightCam);
        specularLight = pow(max(0, dot(N, h)), uSpecularExp);
    }

    vec3 sumCol = diffuseCol.xyz * (ambientLight +
                                    dirLightIntensity * diffuseLight +
                                    uSpecularCol * specularLight);

    fragColor = vec4(sumCol, 1);
}
