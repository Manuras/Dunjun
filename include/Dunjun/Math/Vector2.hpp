#ifndef DUNJUN_MATH_VECTOR2_HPP
#define DUNJUN_MATH_VECTOR2_HPP

#include <Dunjun/Types.hpp>
#include <cmath>

namespace Dunjun
{
struct Vector2
{
	Vector2()
	: x(0)
	, y(0)
	{
	}

	explicit Vector2(f32 xy)
	: x(xy)
	, y(xy)
	{
	}

	Vector2(f32 x, f32 y)
	: x(x)
	, y(y)
	{
	}

	Vector2(f32 xy[2])
	: x(xy[0])
	, y(xy[1])
	{
	}

	f32& operator[](usize index) { return data[index]; }
	const f32& operator[](usize index) const { return data[index]; }

	Vector2 operator+(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator-(const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 operator*(f32 scalar) const
	{
		return Vector2(scalar * x, scalar * y);
	}

	Vector2 operator/(f32 scalar) const
	{
		return Vector2(x / scalar, y / scalar);
	}

	Vector2& operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vector2& operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	Vector2& operator*=(f32 scalar)
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}

	Vector2& operator/=(f32 scalar)
	{
		x /= scalar;
		y /= scalar;

		return *this;
	}

	union
	{
		f32 data[2];
		struct
		{
			f32 x, y;
		};
		struct
		{
			f32 r, g;
		};
		struct
		{
			f32 s, t;
		};
	};
};

inline Vector2 operator*(f32 scalar, const Vector2& vector) { return vector * scalar; }

inline f32 dot(const Vector2& a, const Vector2& b)
{
	return a.x * b.x + a.y * b.y;
}

inline f32 cross(const Vector2& a, const Vector2& b)
{
	return a.x * b.y - b.x * a.y;
}

inline f32 lengthSquared(const Vector2& a)
{
	return dot(a, a);
}

inline f32 length(const Vector2& a)
{
	return std::sqrtf(lengthSquared(a));
}

inline Vector2 normalized(const Vector2& a)
{
	return a  * (1.0f / length(a));
}

} // namespace Dunjun

#endif
