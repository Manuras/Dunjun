#ifndef DUNJUN_SCENE_LIGHTING_HPP
#define DUNJUN_SCENE_LIGHTING_HPP

#include <Dunjun/Math.hpp>

namespace Dunjun
{
struct Attenuation
{
	f32 constant = 1.0f;
	f32 linear = 0.0f;
	f32 quadratic = 1.0f;
};

struct PointLight
{
	Vector3 position = {0, 0, 0};
	Vector3 intensities = Vector3(1);
	Vector3 ambient = Vector3(0.01f);
	Attenuation attenuation;
};
} // namespace Dunjun

#endif
