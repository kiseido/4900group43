#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tex_coord;
layout (location = 2) in vec3 normal;
out vec2 texcoord;
out vec3 varyingNormal;
out vec3 varyingLightDir;
out vec3 varyingVertPos;
out vec3 varyingHalfVector;


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
uniform mat4 normal_matrix;
layout (binding=0) uniform sampler2D s;

void main(void)
{
    if (render_options.lighting != 0) {
        varyingVertPos = (transform_matrix * vec4(position, 1.0)).xyz;
        varyingLightDir = light.position - varyingVertPos;
        varyingNormal = (normal_matrix * vec4(normal, 1.0)).xyz;

        varyingHalfVector =
            normalize(normalize(varyingLightDir)
                + normalize(-varyingVertPos)).xyz;
    }
    gl_Position = projection_matrix * transform_matrix * vec4(position,1.0) + render_options.normalMod*vec4(normal, 0);
    
    texcoord = tex_coord;
}