#ifndef DUNJUN_MATH_MATRIX4_HPP
#define DUNJUN_MATH_MATRIX4_HPP

#include <Dunjun/Math/Vector4.hpp>

#include <array>

namespace Dunjun
{
class Matrix4
{
public:
	Matrix4(); // Indentity

	explicit Matrix4(f32 x); // x * Indentity

	explicit Matrix4(const Vector4& v0,
	                 const Vector4& v1,
	                 const Vector4& v2,
	                 const Vector4& v3);

	Matrix4(const Matrix4& other) = default;

	Vector4& operator[](usize index);
	const Vector4& operator[](usize index) const;

	bool operator==(const Matrix4& m2) const;
	bool operator!=(const Matrix4& m2) const;

	Matrix4 operator+(const Matrix4& other) const;
	Matrix4 operator-(const Matrix4& other) const;

	Matrix4 operator*(const Matrix4& m2) const;
	Vector4 operator*(const Vector4& v) const;
	Matrix4 operator*(f32 scalar) const;

	Matrix4 operator/(f32 scalar) const;

	Matrix4& operator+=(const Matrix4& other);
	Matrix4& operator-=(const Matrix4& other);

	Matrix4& operator*=(const Matrix4& other);

	Matrix4 transpose() const;

	f32 determinant() const;
	Matrix4 inverse() const;

	// std::array<Vector4, 4> data;
	Vector4 data[4];
};

inline Matrix4 operator*(f32 scalar, const Matrix4& m) { return m * scalar; }

inline Matrix4 transpose(const Matrix4& m) { return m.transpose(); }

inline f32 determinant(const Matrix4& m) { return m.determinant(); }

inline Matrix4 inverse(const Matrix4& m) { return m.inverse(); }

inline Matrix4 hadamardProduct(const Matrix4& a, const Matrix4& b)
{
	Matrix4 result;

	for (usize i = 0; i < 4; i++)
		result[i] = a[i] * b[i];

	return result;
}

inline std::ostream& operator<<(std::ostream& os, const Matrix4& m)
{
	os << "Matrix4(";
	for (usize i = 0; i < 4; i++)
	{
		os << "\n\t" << m[i];
		if (i < 3)
			os << ", ";
	}
	os << "\n)";

	return os;
}

} // namespace Dunjun

#endif
