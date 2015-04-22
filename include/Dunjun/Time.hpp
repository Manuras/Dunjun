#ifndef DUNJUN_TIME_HPP
#define DUNJUN_TIME_HPP

#include <Dunjun/Common.hpp>

#include <chrono>

namespace Dunjun
{
class Time
{
public:
	Time()
	: m_microseconds{std::chrono::microseconds{0}}
	{
	}

	// GLOBAL const Time Zero; // TODO(bill): Time::Zero constant


	inline f32 asSeconds() const { return m_microseconds.count() / 1000000.0f; }

	inline s32 asMilliseconds() const
	{
		return static_cast<s32>(m_microseconds.count() / 1000);
	}

	inline s64 asMicroseconds() const { return m_microseconds.count(); }

private:
	friend Time seconds(f32);
	friend Time milliseconds(s32);
	friend Time microseconds(s64);

	explicit Time(s64 microseconds)
	: m_microseconds{std::chrono::microseconds{microseconds}}
	{
	}

	std::chrono::microseconds m_microseconds;
};

inline Time seconds(f32 amount)
{
	return Time(static_cast<s64>(amount * 1000000));
}

inline Time milliseconds(s32 amount)
{
	return Time(static_cast<s64>(amount * 1000));
}

inline Time microseconds(s64 amount)
{
	return Time(amount);
}

inline bool operator==(Time left, Time right)
{
	return left.asMicroseconds() == right.asMicroseconds();
}

inline bool operator!=(Time left, Time right)
{
	return left.asMicroseconds() != right.asMicroseconds();
}

inline bool operator<(Time left, Time right)
{
	return left.asMicroseconds() < right.asMicroseconds();
}

inline bool operator>(Time left, Time right)
{
	return left.asMicroseconds() > right.asMicroseconds();
}

inline bool operator<=(Time left, Time right)
{
	return left.asMicroseconds() <= right.asMicroseconds();
}

inline bool operator>=(Time left, Time right)
{
	return left.asMicroseconds() >= right.asMicroseconds();
}

inline Time operator-(Time right)
{
	return microseconds(-right.asMicroseconds());
}

inline Time operator+(Time left, Time right)
{
	return microseconds(left.asMicroseconds() + right.asMicroseconds());
}

inline Time operator-(Time left, Time right)
{
	return microseconds(left.asMicroseconds() - right.asMicroseconds());
}

inline Time& operator+=(Time& left, Time right)
{
	return left = left + right;
}

inline Time& operator-=(Time& left, Time right)
{
	return left = left - right;
}

inline Time operator*(Time left, f32 right)
{
	return seconds(left.asSeconds() * right);
}

inline Time operator*(Time left, s64 right)
{
	return microseconds(left.asMicroseconds() * right);
}

inline Time operator*(f32 left, Time right)
{
	return seconds(left * right.asSeconds());
}

inline Time operator*(s64 left, Time right)
{
	return microseconds(right.asMicroseconds() * left);
}

inline Time& operator*=(Time& left, f32 right)
{
	return left = left * right;
}

inline Time& operator*=(Time& left, s64 right)
{
	return left = left * right;
}

inline Time operator/(Time left, f32 right)
{
	return seconds(left.asSeconds() / right);
}

inline Time operator/(Time left, s64 right)
{
	return microseconds(left.asMicroseconds() / right);
}

inline Time& operator/=(Time& left, f32 right)
{
	return left = left / right;
}

inline Time& operator/=(Time& left, s64 right)
{
	return left = left / right;
}

inline f32 operator/(Time left, Time right)
{
	return left.asSeconds() / right.asSeconds();
}

inline Time operator%(Time left, Time right)
{
	return microseconds(left.asMicroseconds() % right.asMicroseconds());
}

inline Time& operator%=(Time& left, Time right)
{
	return left = left % right;
}

} // namespacew Dunjun

#endif
