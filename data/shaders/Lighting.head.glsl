#ifndef LIGHTING_HEAD_GLSL
#define LIGHTING_HEAD_GLSL

#include <Common.head.glsl>

struct Attenuation
{
	float constant;
	float linear;
	float quadratic;
};

struct BaseLight
{
	vec3 intensities; // color * intensity
};

struct DirectionalLight
{
	BaseLight base;
	vec3 direction;
};

struct PointLight
{
	BaseLight base;

	vec3 position;
	Attenuation attenuation;

	float range;
};

struct SpotLight
{
	PointLight point;

	float coneAngle;
	vec3 direction;
};

#endif
