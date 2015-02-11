#ifndef DUNJUN_MATH_CONSTANTS_HPP
#define DUNJUN_MATH_CONSTANTS_HPP

#include <Dunjun/Common.hpp>

#include <limits>

namespace Dunjun
{
template <class T>
struct Constants
{
	GLOBAL const T epsilon() { return std::numeric_limits<T>::epsilon() }

	GLOBAL const T zero();
	GLOBAL const T one();
	GLOBAL const T third();
	GLOBAL const T twoThirds();

	GLOBAL const T e();
	GLOBAL const T pi();
	GLOBAL const T tau();

	GLOBAL const T sqrt2();
	GLOBAL const T sqrt3();

	GLOBAL const T goldenRatio();
};

template <>
struct Constants<f32>
{
	Constants() = delete;

	GLOBAL const f32 zero() { return 0.0f; }
	GLOBAL const f32 one() { return 1.0f; }
	GLOBAL const f32 third() { return 0.33333333f; }
	GLOBAL const f32 twoThirds() { return 0.66666667f; }

	GLOBAL const f32 e() { return 2.718281828f; }
	GLOBAL const f32 pi() { return 3.141592654f; }
	GLOBAL const f32 tau() { return 6.283185307f; }

	GLOBAL const f32 sqrt2() { return 1.414213562f; }
	GLOBAL const f32 sqrt3() { return 1.732050808f; }

	GLOBAL const f32 goldenRatio() { return 1.618033989f; }
};

template <>
struct Constants<f64>
{
	Constants() = delete;

	GLOBAL const f64 zero() { return 0.0; }
	GLOBAL const f64 one() { return 1.0; }
	GLOBAL const f64 third() { return 0.333333333333333; }
	GLOBAL const f64 twoThirds() { return 0.666666666666667; }

	GLOBAL const f64 e() { return 2.718281828459045; }
	GLOBAL const f64 pi() { return 3.141592653589793; }
	GLOBAL const f64 tau() { return 6.283185307179586; }

	GLOBAL const f64 sqrt2() { return 1.414213562373095; }
	GLOBAL const f64 sqrt3() { return 1.732050807568877; }

	GLOBAL const f64 goldenRatio() { return 1.618033988749895; }
};

} // namespace Dunjun

#endif
