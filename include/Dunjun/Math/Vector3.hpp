#ifndef DUNJUN_MATH_VECTOR3_HPP
#define DUNJUN_MATH_VECTOR3_HPP

#include <Dunjun/Types.hpp>

#include <Dunjun/Math/Vector2.hpp>

namespace Dunjun
{
struct Vector3
{
	Vector3();

	explicit Vector3(f32 xyz);

	Vector3(f32 x, f32 y, f32 z);

	Vector3(f32 xyz[3]);
	explicit Vector3(const Vector2& other, f32 z);
	Vector3(const Vector3& other) = default;

	inline f32& operator[](usize index) { return data[index]; }
	inline const f32& operator[](usize index) const { return data[index]; }

	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;

	Vector3 operator-() const;

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator*(f32 scalar) const;
	Vector3 operator/(f32 scalar) const;

	// Hadamard Product
	Vector3 operator*(const Vector3& other) const;
	// Hadamard Product
	Vector3 operator/(const Vector3& other) const;
	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);

	Vector3& operator*=(f32 scalar);

	Vector3& operator/=(f32 scalar);

	union
	{
		f32 data[3];
		struct
		{
			f32 x, y, z;
		};
		struct
		{
			f32 r, g, b;
		};
		struct
		{
			f32 s, t, p;
		};
	};
};

inline Vector3 operator*(f32 scalar, const Vector3& vector)
{
	return vector * scalar;
}

f32 dot(const Vector3& a, const Vector3& b);
Vector3 cross(const Vector3& a, const Vector3& b);

f32 lengthSquared(const Vector3& a);
f32 length(const Vector3& a);

Vector3 normalize(const Vector3& a);

inline std::ostream& operator<<(std::ostream& os, const Vector3& v)
{
	return os << "Vector3(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}

} // namespace Dunjun

#endif
