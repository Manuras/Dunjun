#ifndef MATERIAL_HEAD_GLSL
#define MATERIAL_HEAD_GLSL

struct Material
{
	sampler2D diffuseMap;
	vec4 diffuseColor;

	vec4 specularColor;
	float specularExponent;
};

#endif
