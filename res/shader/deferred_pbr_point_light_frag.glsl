#version 330

// Uniforms
uniform vec3 uLightPos;
uniform vec3 uLightAtten;
uniform vec3 uLightInt;

// GBuffer
uniform vec2 uViewportSize;
uniform sampler2D depthMap;
uniform sampler2D normalMap;
uniform sampler2D albedoMap;
uniform sampler2D roughnessMap;
uniform sampler2D metalnessMap;

// Output
out vec4 fragColor;

// Input
// Interpolated view ray direction
in vec2 rayDirVar;

// Constants
const float PI = 3.14159265359;

// Material (for copypaste from skunkwork)
struct Material {
    vec3 albedo;
    float roughness;
    float metalness;
};

vec3 lambertBRFD(vec3 albedo)
{
    return albedo / PI;
}

float ggx(float NoH, float rough)
{
    float a2 = rough * rough;
    a2 *= a2;
    float denom = NoH * NoH * (a2 - 1) + 1;
    return a2 / (PI * denom * denom);
}

vec3 schlick(float VoH, vec3 f0)
{
    return f0 + (1 - f0) * pow(1 - VoH, 5);
}

float schlick_ggx(float NoL, float NoV, float rough)
{
    float k = (rough + 1);
    k *= k * 0.125;
    float gl = NoL / (NoL * (1 - k) + k);
    float gv = NoV / (NoV * (1 - k) + k);
    return gl * gv;
}

vec3 cookTorranceBRDF(float NoL, float NoV, float NoH, float VoH, vec3 F, float rough)
{
    vec3 DFG = ggx(NoH, rough) * F * schlick_ggx(NoL, NoV, rough);
    float denom = 4 * NoL * NoV + 0.0001;
    return DFG / denom;
}

vec3 evalLighting(vec3 v, vec3 n, vec3 l, vec3 intensity, Material mat)
{
    // Default fresnel
    vec3 f0 = mix(vec3(0.04), mat.albedo, mat.metalness);
    float NoV = max(dot(n, v), 0);
    // Dot products
    float NoL = max(dot(n, l), 0);
    vec3 h = normalize(v + l);
    float NoH = max(dot(n, h), 0);
    float VoH = max(dot(v, h), 0);

    // Fresnel
    vec3 F = schlick(VoH, f0);

    // Diffuse amount
    vec3 Ks = F;
    vec3 Kd = (1 - Ks) * (1 - mat.metalness);

    // Return light's contribution
    return (Kd * lambertBRFD(mat.albedo) +
            cookTorranceBRDF(NoL, NoV, NoH, VoH, F, mat.roughness)) *
           intensity * NoL;
}

void main()
{
    vec2 texCoord = gl_FragCoord.xy / uViewportSize;
    // Extract deferred parameters
    float d = texture(depthMap, texCoord).r;
    vec3 n = texture(normalMap, texCoord).rgb;
    Material mat;
    mat.albedo = texture(albedoMap, texCoord).rgb;
    mat.roughness = texture(roughnessMap, texCoord).r;
    mat.metalness = texture(metalnessMap, texCoord).r;

    // Calculate hit position and view ray in camera space
    vec2 uv = gl_FragCoord.xy / uViewportSize;
    // TODO: Pass viewport info as uniform
    // TODO: figure out math of point light transform, pos at 0 working out fine?
    vec2 halfSize = vec2(tan(radians(59.0 * 0.5)) * 16.0 / 9.0, tan(radians(59.0 * 0.5)));
    vec3 hitPos = vec3((2.0 * halfSize * uv) - halfSize, 1.0) * d;
    vec3 v = -normalize(hitPos);
    // Calculate light position and distance
    vec3 toLight = uLightPos - hitPos;
    float lightDist = length(toLight);
    toLight /= lightDist;
    // Attenuate
    float cosTheta = max(dot(n, toLight), 0.0);
    float atten = 1.0 / (uLightAtten[0] + uLightAtten[1] * lightDist + uLightAtten[2] * lightDist * lightDist);
    vec3 lightAttenuated = uLightInt * atten* cosTheta;
    vec3 directCol = evalLighting(v, n, toLight, lightAttenuated, mat);
    fragColor = vec4(directCol, 1);
}
