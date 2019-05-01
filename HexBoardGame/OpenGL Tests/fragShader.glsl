#version 430

in vec2 tc;
out vec4 color;

uniform mat4 transform_matrix;
uniform mat4 projection_matrix;
uniform mat4 camera_matrix;
layout (binding=0) uniform sampler2D s;

void main(void)
{
	color = texture(s,tc);
}
