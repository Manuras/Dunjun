#ifndef DUNJUN_MATH_UNIT_HPP
#define DUNJUN_MATH_UNIT_HPP

#include <chrono>

namespace Dunjun
{
template <template <class> class Derived, class T>
class Unit
{
	template <template <class> class, class>
	friend class Unit;

public:
	using Type = T;

	Unit()
	: m_value{T{0}}
	{
	}

	explicit Unit(T value)
	: m_value{value}
	{
	}

	template <class U>
	explicit Unit(Unit<Derived, U> value)
	: m_value{T{value.m_value}}
	{
	}

	explicit operator T() const { return m_value; }

	bool operator==(Unit<Derived, T> other) const
	{
		return m_value == other.m_value;
	}

	bool operator!=(Unit<Derived, T> other) const { return !operator==(other); }

	bool operator<(Unit<Derived, T> other) const
	{
		return m_value < other.m_value;
	}

	bool operator>(Unit<Derived, T> other) const
	{
		return m_value > other.m_value;
	}

	bool operator<=(Unit<Derived, T> other) const { return !operator>(other); }

	bool operator>=(Unit<Derived, T> other) const { return !operator<(other); }

	Unit<Derived, T> operator-() const { return Unit<Derived, T>{-m_value}; }

	Unit<Derived, T>& operator+=(Unit<Derived, T> other)
	{
		m_value += other.m_value;
		return *this;
	}

	Unit<Derived, T> operator+(Unit<Derived, T> other) const
	{
		return Unit<Derived, T>{m_value + other.m_value};
	}

	Unit<Derived, T>& operator-=(Unit<Derived, T> other)
	{
		m_value -= other.m_value;
		return *this;
	}

	Unit<Derived, T> operator-(Unit<Derived, T> other) const
	{
		return Unit<Derived, T>{m_value - other.m_value};
	}

	Unit<Derived, T>& operator*=(T number)
	{
		m_value *= number;
		return *this;
	}

	Unit<Derived, T> operator*(T number) const
	{
		return Unit<Derived, T>{m_value * number};
	}

	Unit<Derived, T>& operator/=(T number)
	{
		m_value /= number;
		return *this;
	}

	Unit<Derived, T> operator/(T number) const
	{
		return Unit<Derived, T>{m_value / number};
	}

	T operator/(Unit<Derived, T> other) const { return m_value / other.value; }

private:
	T m_value;
};

template <template <class> class Derived, class T>
Unit<Derived, T> operator*(typename std::common_type<T>::type number,
                           const Unit<Derived, T>& value)
{
	return value * number;
}
} // namespace Dunjun

#endif
