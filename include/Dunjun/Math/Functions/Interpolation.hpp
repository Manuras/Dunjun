#ifndef DUNJUN_MATH_FUNCTIONS_INTERPOLATION_HPP
#define DUNJUN_MATH_FUNCTIONS_INTERPOLATION_HPP

#include <Dunjun/Common.hpp>
#include <Dunjun/Math/Quaternion.hpp>

#include <Dunjun/Math/Functions/Common.hpp>

namespace Dunjun
{
namespace Math
{
// Linear Interpolation
template <class T>
inline T lerp(const T& x, const T& y, f32 t)
{
	assert(t >= 0.0f && t <= 1.0f);

	return x * (1.0f - t) + (y * t);
}

// Spherical Linear Interpolation
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

		Radian angle = Math::acos(cosTheta);

		result = Math::sin(Radian(1.0f) - (t * angle)) * x +
		         Math::sin(t * angle) * z;
		result = result * (1.0f / Math::sin(angle));
	}
	return result;
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
