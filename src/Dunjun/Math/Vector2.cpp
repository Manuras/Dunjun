#include <Dunjun/Math/Vector2.hpp>

#include <Dunjun/Math/Functions.hpp>

namespace Dunjun
{
Vector2::Vector2()
: x(0)
, y(0)
{
}

Vector2::Vector2(f32 xy)
: x(xy)
, y(xy)
{
}

Vector2::Vector2(f32 x, f32 y)
: x(x)
, y(y)
{
}

Vector2::Vector2(f32 xy[2])
: x(xy[0])
, y(xy[1])
{
}

bool Vector2::operator==(const Vector2& other) const
{
	for (usize i = 0; i < 2; i++)
	{
		if (data[i] != other.data[i])
			return false;
	}

	return true;
}

bool Vector2::operator!=(const Vector2& other) const
{
	return !Vector2::operator==(other);
}

Vector2 Vector2::operator-() const { return {-x, -y}; }

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(f32 scalar) const
{
	return Vector2(scalar * x, scalar * y);
}

Vector2 Vector2::operator/(f32 scalar) const
{
	return Vector2(x / scalar, y / scalar);
}

// Hadamard Product
Vector2 Vector2::operator*(const Vector2& other) const
{
	Vector2 result;
	for (usize i = 0; i < 2; i++)
		result[i] = data[i] * other.data[i];
	return result;
}

// Hadamard Product
Vector2 Vector2::operator/(const Vector2& other) const
{
	Vector2 result;
	for (usize i = 0; i < 2; i++)
		result[i] = data[i] / other.data[i];
	return result;
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

Vector2& Vector2::operator*=(f32 scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Vector2& Vector2::operator/=(f32 scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}

f32 dot(const Vector2& a, const Vector2& b)
{
	return a.x * b.x + a.y * b.y;
}

f32 cross(const Vector2& a, const Vector2& b)
{
	return a.x * b.y - b.x * a.y;
}

f32 lengthSquared(const Vector2& a) { return dot(a, a); }

f32 length(const Vector2& a) { return Math::sqrt(lengthSquared(a)); }

Vector2 normalize(const Vector2& a) { return a * (1.0f / length(a)); }

} // namespace Dunjun
