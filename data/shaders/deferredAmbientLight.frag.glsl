#version 120

struct BaseLight
{
	vec3 intensities; // color * intensity
};

uniform BaseLight u_light;

void main()
{
	gl_FragColor = vec4(u_light.intensities, 0.0);
}
