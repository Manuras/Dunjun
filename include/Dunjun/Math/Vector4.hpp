#ifndef DUNJUN_MATH_VECTOR4_HPP
#define DUNJUN_MATH_VECTOR4_HPP

#include <Dunjun/Types.hpp>

#include <Dunjun/Math/Vector3.hpp>

namespace Dunjun
{
struct Vector4
{
	Vector4();
	explicit Vector4(f32 xyzw);
	Vector4(f32 x, f32 y, f32 z, f32 w);
	Vector4(f32 xyzw[4]);
	explicit Vector4(const Vector2& xy, f32 z, f32 w);
	explicit Vector4(const Vector2& xy, const Vector2& zw);
	explicit Vector4(const Vector3& xyz, f32 w);
	Vector4(const Vector4& other) = default;

	inline f32& operator[](usize index) { return data[index]; }
	inline const f32& operator[](usize index) const { return data[index]; }

	bool operator==(const Vector4& other) const;
	bool operator!=(const Vector4& other) const;
	
	Vector4 operator-() const;

	Vector4 operator+(const Vector4& other) const;

	Vector4 operator-(const Vector4& other) const;

	Vector4 operator*(f32 scalar) const;

	// Hadamard Product
	Vector4 operator*(const Vector4& other) const;
	// Hadamard Product
	Vector4 operator/(const Vector4& other) const;
	Vector4 operator/(f32 scalar) const;

	Vector4& operator+=(const Vector4& other);
	Vector4& operator-=(const Vector4& other);
	Vector4& operator*=(f32 scalar);
	Vector4& operator/=(f32 scalar);

	union
	{
		f32 data[4];
		struct
		{
			f32 x, y, z, w;
		};
		struct
		{
			f32 r, g, b, a;
		};
		struct
		{
			f32 s, t, p, q;
		};
	};
};

inline Vector4 operator*(f32 scalar, const Vector4& vector)
{
	return vector * scalar;
}

f32 dot(const Vector4& a, const Vector4& b);

f32 lengthSquared(const Vector4& a);
f32 length(const Vector4& a);
Vector4 normalize(const Vector4& a);

inline std::ostream& operator<<(std::ostream& os, const Vector4& v)
{
	return os << "Vector4(" << v[0] << ", " << v[1] << ", " << v[2] << ", "
	          << v[3] << ")";
}

} // namespace Dunjun

#endif
