#include <Dunjun/Math/Vector4.hpp>

namespace Dunjun
{
Vector4::Vector4()
: x(0)
, y(0)
, z(0)
, w(0)
{
}

Vector4::Vector4(f32 xyzw)
: x(xyzw)
, y(xyzw)
, z(xyzw)
, w(xyzw)
{
}

Vector4::Vector4(f32 x, f32 y, f32 z, f32 w)
: x(x)
, y(y)
, z(z)
, w(w)
{
}

Vector4::Vector4(f32 xyzw[4])
: x(xyzw[0])
, y(xyzw[1])
, z(xyzw[2])
, w(xyzw[3])
{
}

Vector4::Vector4(const Vector2& xy, f32 z, f32 w)
: x(xy.x)
, y(xy.y)
, z(z)
, w(w)
{
}

Vector4::Vector4(const Vector2& xy, const Vector2& zw)
: x(xy.x)
, y(xy.y)
, z(zw.x)
, w(zw.y)
{
}

Vector4::Vector4(const Vector3& xyz, f32 w)
: x(xyz.x)
, y(xyz.y)
, z(xyz.z)
, w(w)
{
}

bool Vector4::operator==(const Vector4& other) const
{
	for (usize i = 0; i < 4; i++)
	{
		if (data[i] != other.data[i])
			return false;
	}

	return true;
}

bool Vector4::operator!=(const Vector4& other) const
{
	return !operator==(other);
}

Vector4 Vector4::operator-() const { return {-x, -y, -z, -w}; }

Vector4 Vector4::operator+(const Vector4& other) const
{
	return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4 Vector4::operator-(const Vector4& other) const
{
	return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4 Vector4::operator*(f32 scalar) const
{
	return Vector4(scalar * x, scalar * y, scalar * z, scalar * w);
}

// Hadamard Product
Vector4 Vector4::operator*(const Vector4& other) const
{
	Vector4 result;
	for (usize i = 0; i < 4; i++)
		result[i] = data[i] * other.data[i];
	return result;
}

// Hadamard Product
Vector4 Vector4::operator/(const Vector4& other) const
{
	Vector4 result;
	for (usize i = 0; i < 4; i++)
		result[i] = data[i] / other.data[i];
	return result;
}

Vector4 Vector4::operator/(f32 scalar) const
{
	return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
}

Vector4& Vector4::operator+=(const Vector4& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;

	return *this;
}

Vector4& Vector4::operator-=(const Vector4& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;

	return *this;
}

Vector4& Vector4::operator*=(f32 scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;

	return *this;
}

Vector4& Vector4::operator/=(f32 scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;

	return *this;
}

f32 dot(const Vector4& a, const Vector4& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

f32 lengthSquared(const Vector4& a) { return dot(a, a); }

f32 length(const Vector4& a) { return std::sqrt(lengthSquared(a)); }

Vector4 normalize(const Vector4& a) { return a * (1.0f / length(a)); }

} // namespace Dunjun
