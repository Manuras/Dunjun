#include <Dunjun/Math/Vector3.hpp>

#include <Dunjun/Math/Functions.hpp>

namespace Dunjun
{
Vector3::Vector3()
: x(0)
, y(0)
, z(0)
{
}

Vector3::Vector3(f32 xyz)
: x(xyz)
, y(xyz)
, z(xyz)
{
}

Vector3::Vector3(f32 x, f32 y, f32 z)
: x(x)
, y(y)
, z(z)
{
}

Vector3::Vector3(f32 xyz[3])
: x(xyz[0])
, y(xyz[1])
, z(xyz[2])
{
}

Vector3::Vector3(const Vector2& other, f32 z)
: x(other.x)
, y(other.y)
, z(z)
{
}

bool Vector3::operator==(const Vector3& other) const
{
	for (usize i = 0; i < 3; i++)
	{
		if (data[i] != other.data[i])
			return false;
	}

	return true;
}

bool Vector3::operator!=(const Vector3& other) const
{
	return !Vector3::operator==(other);
}

Vector3 Vector3::operator-() const { return {-x, -y, -z}; }

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(f32 scalar) const
{
	return Vector3(scalar * x, scalar * y, scalar * z);
}

Vector3 Vector3::operator/(f32 scalar) const
{
	return Vector3(x / scalar, y / scalar, z / scalar);
}

// Hadamard Product
Vector3 Vector3::operator*(const Vector3& other) const
{
	Vector3 result;
	for (usize i = 0; i < 3; i++)
		result[i] = data[i] * other.data[i];
	return result;
}

// Hadamard Product
Vector3 Vector3::operator/(const Vector3& other) const
{
	Vector3 result;
	for (usize i = 0; i < 3; i++)
		result[i] = data[i] / other.data[i];
	return result;
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

Vector3& Vector3::operator*=(f32 scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

Vector3& Vector3::operator/=(f32 scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

f32 dot(const Vector3& a, const Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 cross(const Vector3& a, const Vector3& b)
{
	return Vector3(a.y * b.z - b.y * a.z, // x
	               a.z * b.x - b.z * a.x, // y
	               a.x * b.y - b.x * a.y  // z
	               );
}

f32 lengthSquared(const Vector3& a) { return dot(a, a); }

f32 length(const Vector3& a) { return Math::sqrt(lengthSquared(a)); }

Vector3 normalize(const Vector3& a) { return a * (1.0f / length(a)); }
} // namespace Dunjun
