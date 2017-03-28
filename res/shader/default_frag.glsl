#version 330

// Material
uniform vec3 uSpecularCol;
uniform float uSpecularExp;

// Textures
uniform sampler2D diffuseSampler;

// Interpolated inputs
struct VertexAttr {
    vec3 pos;
    vec3 norm;
    vec2 tex;
};
in VertexAttr attrVar;

// Outputs
out vec4 fragColor;

// Constants
const vec3 ambientLight = vec3(0.2, 0.2, 0.2);
const float dirLightIntensity = 0.8f;
const vec3 toLightCam = normalize(vec3(0, 0, -1));

void main()
{
    // Diffuse color
    vec3 diffuseCol = texture(diffuseSampler, attrVar.tex).xyz;

    // Lighting
    vec3 N = normalize(attrVar.norm);
    float diffuseLight = max(0, dot(N, toLightCam));

    float specularLight = 0;
    if (diffuseLight > 0) {
        vec3 V = -normalize(attrVar.pos);
        vec3 h = normalize(V + toLightCam);
        specularLight = pow(max(0, dot(N, h)), uSpecularExp);
    }

    vec3 sumCol = diffuseCol.xyz * (ambientLight +
                                    dirLightIntensity * diffuseLight +
                                    uSpecularCol * specularLight);

    fragColor = vec4(sumCol, 1);
}
