#include <Dunjun/Math/Functions/Common.hpp>

#include <Dunjun/Math/Quaternion.hpp>

#include <cmath>
#include <cfenv>

namespace Dunjun
{
namespace Math
{
// Trigonometric
f32 sin(const Radian& theta) { return std::sin(static_cast<f32>(theta)); }
f32 cos(const Radian& theta) { return std::cos(static_cast<f32>(theta)); }
f32 tan(const Radian& theta) { return std::tan(static_cast<f32>(theta)); }

Radian asin(f32 a) { return Radian(std::asin(a)); }
Radian acos(f32 a) { return Radian(std::acos(a)); }
Radian atan(f32 a) { return Radian(std::atan(a)); }
Radian atan2(f32 y, f32 x) { return Radian(std::atan2(y, x)); }

// Hyperbolic
f32 sinh(f32 x) { return std::sinh(x); }
f32 cosh(f32 x) { return std::cosh(x); }
f32 tanh(f32 x) { return std::tanh(x); }

f32 asinh(f32 x) { return std::asinh(x); }
f32 acosh(f32 x) { return std::acosh(x); }
f32 atanh(f32 x) { return std::atanh(x); }

// Power
f32 pow(f32 x, f32 y) { return std::pow(x, y); }

f32 sqrt(f32 x) { return std::sqrt(x); }

f32 cbrt(f32 x) { return std::cbrt(x); }

f32 hypotenuse(f32 x, f32 y) { return std::hypot(x, y); }

f32 fastInvSqrt(f32 number)
{
	u32 i;
	f32 x2, y;
	const f32 threeHalfs = 1.5f;

	x2 = number * 0.5f;
	y = number;
	i = pseudo_cast<u32>(y); // Evil floating point bit level hacking
	//	i = 0x5f3759df - (i >> 1);           // What the fuck?
	i = 0x5f375a86 - (i >> 1); // What the fuck? Improved!
	y = pseudo_cast<f32>(i);
	y = y * (threeHalfs - (x2 * y * y)); // 1st iteration
	//	y = y * (threeHalfs - (x2 * y * y)); // 2nd iteration, this can be
	// removed

	return y;
}

// Exponential and Logarithm
f32 exp(f32 x) // e^x
{
	return std::exp(x);
}
f32 exp2(f32 x) // 2^x
{
	return std::exp2(x);
}
f32 ln(f32 x) { return std::log(x); }
f32 ln1p(f32 x) // ln(1 + x)
{
	return std::log1p(x);
}
f32 log2(f32 x) { return std::log2(x); }

f32 log10(f32 x) { return std::log10(x); }
f32 logBase(f32 x, f32 base) { return ln(x) * (1.0f / ln(base)); }

// Rounding
f32 ceil(f32 x) { return std::ceil(x); }
f32 floor(f32 x) { return std::floor(x); }
f32 mod(f32 x, f32 y)
{
	f32 result = std::remainder(Math::abs(x), (y = Math::abs(y)));
	if (std::signbit(result))
		result += y;
	return std::copysign(result, x);
}
f32 truncate(f32 x)
{
	u32 i = pseudo_cast<u32>(x);
	s32 exponent = (i >> 23) & 0xFF; // extract exponent field
	s32 fractionalBits = 0x7F + 23 - exponent;
	if (fractionalBits > 23) // abs(x) < 1.0f
		return 0.0f;
	if (fractionalBits > 0)
		i &= ~((1u << fractionalBits) - 1);
	return pseudo_cast<f32>(i);
}
f32 round(f32 x)
{
	std::fenv_t saveEnv;
	std::feholdexcept(&saveEnv);
	f32 result = std::rint(x);
	if (std::fetestexcept(FE_INEXACT))
	{
		std::fesetround(FE_TOWARDZERO);
		result = std::rint(std::copysign(0.5f + Math::abs(x), x));
	}
	std::feupdateenv(&saveEnv);
	return result;
}

s32 sign(s32 x)
{
	u32 i = reinterpret_cast<const u32&>(x);
	i &= 0x80000000ul;
	if (i)
		return -1;
	return 1;
}

s64 sign(s64 x)
{
	u64 i = reinterpret_cast<const u64&>(x);
	i &= 0x8000000000000000ull;
	if (i)
		return -1;
	return 1;
}

f32 sign(f32 x)
{
	u32 i = reinterpret_cast<const u32&>(x);
	i &= 0x80000000ul;
	if (i)
		return -1.0f;
	return 1.0f;
}

// Other
f32 abs(f32 x)
{
	u32 i = reinterpret_cast<const u32&>(x);
	i &= 0x7FFFFFFFul;
	return reinterpret_cast<const f32&>(i);
}
s8 abs(s8 x)
{
	u8 i = reinterpret_cast<const u8&>(x);
	i &= 0x7Fu;
	return reinterpret_cast<const s8&>(i);
}
s16 abs(s16 x)
{
	u16 i = reinterpret_cast<const u16&>(x);
	i &= 0x7FFFu;
	return reinterpret_cast<const s16&>(i);
}
s32 abs(s32 x)
{
	u32 i = reinterpret_cast<const u32&>(x);
	i &= 0x7FFFFFFFul;
	return reinterpret_cast<const s32&>(i);
}
s64 abs(s64 x)
{
	u64 i = reinterpret_cast<const u64&>(x);
	i &= 0x7FFFFFFFFFFFFFFFull;
	return reinterpret_cast<const s64&>(i);
}
} // namespace Math
} // namespace Dunjun
