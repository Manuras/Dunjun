#ifndef DUNJUN_SCENE_LIGHTING_HPP
#define DUNJUN_SCENE_LIGHTING_HPP

#include <Dunjun/Math.hpp>
#include <Dunjun/Color.hpp>

namespace Dunjun
{
struct Attenuation
{
	f32 constant{1.0f};
	f32 linear{0.0f};
	f32 quadratic{1.0f};
};

struct BaseLight
{
	Color color{0xFF, 0xFF, 0xFF};
	f32 intensity{1.0f};
};

struct DirectionalLight : BaseLight
{
	Vector3 direction;
};

struct PointLight : BaseLight
{
	Vector3 position{0, 0, 0};

	Attenuation attenuation;

	mutable f32 range{16.0f};

	inline void calculateRange() const
	{
		f32 i{intensity * (f32)std::max(color.r, std::max(color.g, color.b))};

		f32 r{-attenuation.linear +
		      Math::sqrt(attenuation.linear * attenuation.linear -
		                 4.0f * attenuation.quadratic *
		                     (attenuation.constant - i))};
		r /= 2.0f * attenuation.quadratic;

		range = r;
	}
};
} // namespace Dunjun

#endif
