#version 330

// Common uniforms
uniform float uHalfFovX;

// Custom uniforms
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

// Constants
const float PI = 3.14159265359;

// Material (for copypaste from skunkwork)
struct Material {
    vec3 albedo;
    float roughness;
    float metalness;
};

// Diffuse BRDF: Lambert
vec3 lambertBRFD(vec3 albedo)
{
    return albedo / PI;
}

// Normal Distribution Function: GGX/Trowbridge-Reitz
float ggx(float NoH, float rough)
{
    float a2 = rough * rough;
    a2 *= a2;
    float denom = NoH * NoH * (a2 - 1) + 1;
    return a2 / (PI * denom * denom);
}

// Fresnel: Schlick
vec3 schlick(float VoH, vec3 f0)
{
    return f0 + (1 - f0) * pow(1 - VoH, 5);
}

// Specular Geometric Attenuation: modified Schlick
float schlick_ggx(float NoL, float NoV, float rough)
{
    float k = (rough + 1);
    k *= k * 0.125;
    float gl = NoL / (NoL * (1 - k) + k);
    float gv = NoV / (NoV * (1 - k) + k);
    return gl * gv;
}

// Specular BRDF: Cook-Torrance
// Taken from the Siggraph 2013 presentation by Brian Karis (Epic Games)
//            D(h)F(v,h)G(l,v,h)
// f(l,v) = ----------------------
//               4(n.l)(n.v)
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
    vec2 uv = gl_FragCoord.xy / uViewportSize;
    // Extract deferred parameters
    float posZ = texture(depthMap, uv).r;
    vec3 n = texture(normalMap, uv).rgb;
    Material mat;
    mat.albedo = texture(albedoMap, uv).rgb;
    mat.roughness = texture(roughnessMap, uv).r;
    mat.metalness = texture(metalnessMap, uv).r;

    // Calculate hit position and view ray in camera space
    float tanHalfFovX = tan(uHalfFovX);
    vec2 viewportSkew = vec2(tanHalfFovX, tanHalfFovX / (uViewportSize.x / uViewportSize.y));
    vec3 hitPos = vec3(2 * viewportSkew * uv - viewportSkew, 1) * posZ;
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
