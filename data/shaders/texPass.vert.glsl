#version 120

attribute vec3 a_position;
attribute vec2 a_texCoord;

uniform vec3 u_scale;

varying vec2 v_texCoord;

void main()
{
	v_texCoord = a_texCoord;

	gl_Position = vec4(u_scale * a_position, 1.0);
}
