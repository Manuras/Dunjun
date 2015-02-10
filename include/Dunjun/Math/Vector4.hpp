#ifndef DUNJUN_MATH_VECTOR4_HPP
#define DUNJUN_MATH_VECTOR4_HPP

#include <Dunjun/Types.hpp>
#include <cmath>

#include <Dunjun/Math/Vector3.hpp>

namespace Dunjun
{
struct Vector4
{
	Vector4()
	: x(0)
	, y(0)
	, z(0)
	, w(0)
	{
	}

	explicit Vector4(f32 xyzw)
	: x(xyzw)
	, y(xyzw)
	, z(xyzw)
	, w(xyzw)
	{
	}

	Vector4(f32 x, f32 y, f32 z, f32 w)
	: x(x)
	, y(y)
	, z(z)
	, w(w)
	{
	}

	Vector4(f32 xyzw[4])
	: x(xyzw[0])
	, y(xyzw[1])
	, z(xyzw[2])
	, w(xyzw[3])
	{
	}

	explicit Vector4(const Vector2& xy, f32 z, f32 w)
	: x(xy.x)
	, y(xy.y)
	, z(z)
	, w(w)
	{
	}

	explicit Vector4(const Vector2& xy, const Vector2& zw)
	: x(xy.x)
	, y(xy.y)
	, z(zw.x)
	, w(zw.y)
	{
	}

	explicit Vector4(const Vector3& xyz, f32 w)
	: x(xyz.x)
	, y(xyz.y)
	, z(xyz.z)
	, w(w)
	{
	}

	f32& operator[](usize index) { return data[index]; }
	const f32& operator[](usize index) const { return data[index]; }

	bool operator==(const Vector4& other) const
	{
		for (usize i = 0; i < 4; i++)
		{
			if (data[i] != other.data[i])
				return false;
		}

		return true;
	}

	bool operator!=(const Vector4& other) const
	{
		return !operator==(other);
	}

	Vector4 operator+(const Vector4& other) const
	{
		return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	Vector4 operator-(const Vector4& other) const
	{
		return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	Vector4 operator*(f32 scalar) const
	{
		return Vector4(scalar * x, scalar * y, scalar * z, scalar * w);
	}

	// Hadamard Product
	Vector4 operator*(const Vector4& other) const
	{
		Vector4 result;
		for (usize i = 0; i < 4; i++)
			result[i] = data[i] * other.data[i];
		return result;
	}

	Vector4 operator/(f32 scalar) const
	{
		return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
	}

	Vector4& operator+=(const Vector4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	Vector4& operator-=(const Vector4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	Vector4& operator*=(f32 scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;

		return *this;
	}

	Vector4& operator/=(f32 scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;

		return *this;
	}

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

inline f32 dot(const Vector4& a, const Vector4& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline f32 lengthSquared(const Vector4& a) { return dot(a, a); }

inline f32 length(const Vector4& a) { return std::sqrtf(lengthSquared(a)); }

inline Vector4 normalized(const Vector4& a) { return a * (1.0f / length(a)); }

inline std::ostream& operator<<(std::ostream& os, const Vector4& v)
{
	return os << "Vector4(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
}

} // namespace Dunjun

#endif
