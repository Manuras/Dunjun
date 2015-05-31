#ifndef DUNJUN_MATH_FUNCTIONS_INTERPOLATION_HPP
#define DUNJUN_MATH_FUNCTIONS_INTERPOLATION_HPP

#include <Dunjun/Common.hpp>
#include <Dunjun/Math/Quaternion.hpp>

#include <Dunjun/Math/Functions/Common.hpp>

#include <cassert>

namespace Dunjun
{
namespace Math
{
// Linear Interpolation
template <typename T>
inline T lerp(const T& x, const T& y, f32 t)
{
	assert(t >= 0.0f && t <= 1.0f && "Math::lerp `t` out range (0..1).");

	return x * (1.0f - t) + (y * t);
}

// Spherical Linear Interpolation
inline Quaternion slerp(const Quaternion& x, const Quaternion& y, f32 t)
{
	assert(t >= 0.0f && t <= 1.0f && "Math::lerp `t` out range (0..1).");

	Quaternion z{y};

	f32 cosTheta{dot(x, y)};

	if (cosTheta < 0.0f)
	{
		z = -y;
		cosTheta = -cosTheta;
	}

	if (cosTheta > 1.0f)
	{
		return Quaternion{lerp(x.x, y.x, t),
		                  lerp(x.y, y.y, t),
		                  lerp(x.z, y.z, t),
		                  lerp(x.w, y.w, t)};
	}

	Radian angle{Math::acos(cosTheta)};

	Quaternion result{Math::sin(Radian{1.0f} - (t * angle)) * x +
	                  Math::sin(t * angle) * z};
	return result * (1.0f / Math::sin(angle));
}

// Shoemake's Quaternion Curves
// Sqherical Cubic Interpolation
inline Quaternion squad(const Quaternion& p,
                        const Quaternion& a,
                        const Quaternion& b,
                        const Quaternion& q,
                        f32 t)
{
	return slerp(slerp(p, q, t), slerp(a, b, t), 2.0f * t * (1.0f - t));
}

} // namespace Math
} // namespace Dunjun

#endif
