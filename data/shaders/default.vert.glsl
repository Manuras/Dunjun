#version 120

struct Transform
{
	vec3 position;
	vec4 orientation;
	vec3 scale;
};

vec3 quaternionRotate(vec4 q, vec3 v)
{
	vec3 t = 2.0 * cross(q.xyz, v);
	return (v + q.w * t + cross(q.xyz, t));
}

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
