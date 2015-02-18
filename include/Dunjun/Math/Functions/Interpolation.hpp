#ifndef DUNJUN_MATH_FUNCTIONS_INTERPOLATION_HPP
#define DUNJUN_MATH_FUNCTIONS_INTERPOLATION_HPP

#include <Dunjun/Common.hpp>
#include <Dunjun/Math/Quaternion.hpp>

#include <cmath>

namespace Dunjun
{
template <class T>
inline f32 lerp(const T& x, const T& y, f32 t)
{
	assert(t >= 0.0f && t <= 1.0f);

	return x * (1.0f - t) + (y * t);
}

inline Quaternion slerp(const Quaternion& x, const Quaternion& y, f32 t)
{
	assert(t >= 0.0f && t <= 1.0f);

	Quaternion z = y;

	f32 cosTheta = dot(x, y);

	if (cosTheta < 0.0f)
	{
		z = -y;
		cosTheta = -cosTheta;
	}

	Quaternion result;

	if (cosTheta > 1.0f)
	{
		result = Quaternion(lerp(x.x, y.x, t),
		                    lerp(x.y, y.y, t),
		                    lerp(x.z, y.z, t),
		                    lerp(x.w, y.w, t));
	}
	else
	{

		f32 angle = std::acos(cosTheta);

		result = std::sin(1.0f - t * angle) * x + std::sin(t * angle) * z;
		result = result * (1.0f / std::sin(angle));
	}
	return result;
}

} // namespace Dunjun

#endif
