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

attribute vec2 a_position;
attribute vec3 a_color;
attribute vec2 a_texCoord;

varying vec3 v_color;
varying vec2 v_texCoord;

uniform mat4 u_camera;
uniform Transform u_transform = {vec3(0), vec4(0, 0, 0, 1), vec3(1)};

void main()
{
	v_color = a_color;
	v_texCoord = a_texCoord.st;

	// v' = proj * view * transform * v;
	vec3 pos = vec3(a_position, 0.0);
	pos = u_transform.position + quaternionRotate(u_transform.orientation, u_transform.scale * pos);
	gl_Position = u_camera * vec4(pos, 1.0);
}
