#version 120

#include <Common.head.glsl>

attribute vec3 a_position;
attribute vec2 a_texCoord;
attribute vec3 a_color;
attribute vec3 a_normal;

varying vec3 v_position_ws;

varying vec3 v_position;
varying vec2 v_texCoord;
varying vec3 v_color;
varying vec3 v_normal;

uniform mat4 u_camera;
uniform Transform u_transform;

void main()
{
	v_position = a_position;
	v_texCoord = a_texCoord.st;
	v_color = a_color;
	v_normal = a_normal;

	// v' = proj * view * transform * v;
	vec3 pos = a_position;
	pos = u_transform.position + quaternionRotate(u_transform.orientation, u_transform.scale * pos);
	v_position_ws = pos;

	gl_Position = u_camera * vec4(pos, 1.0);
}
