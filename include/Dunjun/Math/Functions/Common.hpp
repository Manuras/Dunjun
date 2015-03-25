#ifndef DUNJUN_MATH_FUNCTIONS_COMMON_HPP
#define DUNJUN_MATH_FUNCTIONS_COMMON_HPP

#include <Dunjun/Math/Angle.hpp>

#include <algorithm>

namespace Dunjun
{
namespace Math
{
// Trigonometric
f32 sin(const Radian& theta);
f32 cos(const Radian& theta);
f32 tan(const Radian& theta);

Radian asin(f32 a);
Radian acos(f32 a);
Radian atan(f32 a);
Radian atan2(f32 y, f32 x);

// Hyperbolic
f32 sinh(f32 x);
f32 cosh(f32 x);
f32 tanh(f32 x);

f32 asinh(f32 x);
f32 acosh(f32 x);
f32 atanh(f32 x);

// Power
f32 pow(f32 x, f32 y);
f32 sqrt(f32 x);
f32 cbrt(f32 x);
f32 hypotenuse(f32 x, f32 y);

f32 fastInvSqrt(f32 x);

// Exponential and Logarithm
f32 exp(f32 x);  // e^x
f32 exp2(f32 x); // 2^x
f32 ln(f32 x);
f32 ln1p(f32 x); // ln(1 + x)
f32 log2(f32 x);
f32 log10(f32 x);
f32 logBase(f32 x, f32 base);

// Rounding
f32 ceil(f32 x);
f32 floor(f32 x);
f32 mod(f32 x, f32 y);
f32 truncate(f32 x);
f32 round(f32 x);

s32 sign(s32 x);
s64 sign(s64 x);
f32 sign(f32 x);

// Other
f32 abs(f32 x);
s8  abs(s8 x);
s16 abs(s16 x);
s32 abs(s32 x);
s64 abs(s64 x);


template <class T>
T clamp(const T& x, const T& lower, const T& upper)
{
	return std::max(lower, std::min(x, upper));
}

template <class T>
inline T kroneckerDelta(const T& i, const T& j)
{
	return i == j ? T(1) : T(0);
}
} // namespace Math
} // namespace Dunjun

#endif
