#version 430

in vec2 texcoord;
in vec3 varyingNormal;
in vec3 varyingLightDir;
in vec3 varyingVertPos;
in vec3 varyingHalfVector;

out vec4 fragColor;


struct PositionalLight
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec3 position;
};
struct Material
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};
struct RenderOptions {
    int special;
    int lighting;
    vec3 color;
    float normalMod;
    float scaleMod;
};

uniform RenderOptions render_options;
uniform vec4 globalAmbient;
uniform PositionalLight light;
uniform Material material;
uniform mat4 transform_matrix;
uniform mat4 projection_matrix;
uniform mat4 camera_matrix;
layout (binding=0) uniform sampler2D texturesample;

void main(void)
{
    vec4 texColor = texture(texturesample, texcoord);

    if (render_options.lighting != 0) {
        vec4 ambColor = texColor * material.ambient;
        vec4 diffColor = texColor * material.diffuse;
        vec4 specColor = texColor * material.specular;
        // normalize the light, normal, and view vectors:
        vec3 L = normalize(varyingLightDir);
        vec3 N = normalize(varyingNormal);
        vec3 V = normalize(-varyingVertPos);

        // get the angle between the light and surface normal:
        float cosTheta = dot(L, N);

        // halfway vector varyingHalfVector was computed in the vertex shader,
        // and interpolated prior to reaching the fragment shader.
        // It is copied into variable H here for convenience later.
        vec3 H = normalize(varyingHalfVector);

        // get angle between the normal and the halfway vector
        float cosPhi = dot(H, N);

        // compute ADS contributions (per pixel):
        vec3 ambient = ((globalAmbient * ambColor) + (light.ambient * ambColor)).xyz;
        vec3 diffuse = light.diffuse.xyz * diffColor.xyz * max(cosTheta, 0.0);
        vec3 specular = light.specular.xyz * specColor.xyz * pow(max(cosPhi, 0.0), material.shininess*3.0);
        fragColor = vec4((ambient + diffuse + specular), 1.0);
    }
    else if (render_options.special == 2) {
        fragColor = vec4(render_options.color,1);
    }
    //fragColor = texColor;
}
