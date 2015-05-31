#ifndef DUNJUN_MATH_ANGLE_HPP
#define DUNJUN_MATH_ANGLE_HPP

#include <Dunjun/Types.hpp>
#include <Dunjun/Math/Constants.hpp>
#include <Dunjun/Math/Unit.hpp>

#include <ostream>

namespace Dunjun
{
namespace Impl
{
template <typename T>
class Radian;

// Degree
template <typename T>
class Degree : public Unit<Degree, T>
{
public:
	Degree() {}

	explicit Degree(T value)
	: Unit<Dunjun::Impl::Degree, T>(value)
	{
	}

	Degree(Unit<Dunjun::Impl::Degree, T> value)
	: Unit<Dunjun::Impl::Degree, T>(value)
	{
	}

	template <class U>
	explicit Degree(Unit<Dunjun::Impl::Degree, U> value)
	: Unit<Dunjun::Impl::Degree, T>(value)
	{
	}

	Degree(Unit<Radian, T> value);
};

// Radian
template <typename T>
class Radian : public Unit<Radian, T>
{
public:
	Radian() {}

	explicit Radian(T value)
	: Unit<Dunjun::Impl::Radian, T>(value)
	{
	}

	Radian(Unit<Dunjun::Impl::Radian, T> value)
	: Unit<Dunjun::Impl::Radian, T>(value)
	{
	}
	template <class U>
	explicit Radian(Unit<Dunjun::Impl::Radian, U> value)
	: Unit<Dunjun::Impl::Radian, T>(value)
	{
	}

	Radian(Unit<Degree, T> value);
};

template <typename T>
Degree<T>::Degree(Unit<Radian, T> value)
: Unit<Dunjun::Impl::Degree, T>(T(360) * T(value) / Math::Tau)
{
}

template <typename T>
Radian<T>::Radian(Unit<Degree, T> value)
: Unit<Dunjun::Impl::Radian, T>(T(value) * Math::Tau / T(360))
{
}
} // namespace Impl

using Radian = Impl::Radian<f32>;
using Degree = Impl::Degree<f32>;

} // namespace Dunjun

#endif
