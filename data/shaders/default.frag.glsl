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

uniform mat4 u_camera;
uniform Transform u_transform = {vec3(0), vec4(0, 0, 0, 1), vec3(1)};

uniform sampler2D u_tex;

varying vec3 v_position;
varying vec2 v_texCoord;
varying vec3 v_color;
varying vec3 v_normal;

void main()
{
	vec4 texColor = texture2D(u_tex, v_texCoord).rgba;
	if (texColor.a < 0.5)
		discard;

	vec3 normal = normalize(quaternionRotate(u_transform.orientation, v_normal));

	vec3 pos = a_position;
	pos = u_transform.position + quaternionRotate(u_transform.orientation, u_transform.scale * pos);


	vec3 lightPos = vec3(5, 5, 5);

	vec3 surfaceToLight = lightPos - pos;

	float brightness = dot(normal, surfaceToLight) / (length(normal) * length(surfaceToLight));
	brightness = clamp(brightness, 0, 1); // make sure brightness doesn't exceed 1 nor be negative


	vec3 gamma = vec3(1.0 / 2.2);
	vec3 color = texColor.rgb * v_color;

	color = brightness * color;

	gl_FragColor = vec4(pow(color, gamma), 1.0);
}
