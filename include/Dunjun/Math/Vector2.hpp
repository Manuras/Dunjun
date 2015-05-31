#ifndef DUNJUN_MATH_VECTOR2_HPP
#define DUNJUN_MATH_VECTOR2_HPP

#include <Dunjun/Types.hpp>
#include <iostream>

namespace Dunjun
{
struct Vector2
{
	Vector2();
	explicit Vector2(f32 xy);
	Vector2(f32 x, f32 y);
	Vector2(f32 xy[2]);

	Vector2(const Vector2& other) = default;

	inline f32& operator[](usize index) { return data[index]; }
	inline const f32& operator[](usize index) const { return data[index]; }

	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;

	Vector2 operator-() const;

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;

	Vector2 operator*(f32 scalar) const;

	Vector2 operator/(f32 scalar) const;

	// Hadamard Product
	Vector2 operator*(const Vector2& other) const;
	// Hadamard Product
	Vector2 operator/(const Vector2& other) const;

	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2& operator*=(f32 scalar);

	Vector2& operator/=(f32 scalar);

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

inline Vector2 operator*(f32 scalar, const Vector2& vector)
{
	return vector * scalar;
}

f32 dot(const Vector2& a, const Vector2& b);
f32 cross(const Vector2& a, const Vector2& b);

f32 lengthSquared(const Vector2& a);
f32 length(const Vector2& a);

Vector2 normalize(const Vector2& a);

inline std::ostream& operator<<(std::ostream& os, const Vector2& v)
{
	return os << "Vector2(" << v[0] << ", " << v[1] << ")";
}
} // namespace Dunjun

#endif
