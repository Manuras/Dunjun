#ifndef DUNJUN_MATH_QUATERNION_HPP
#define DUNJUN_MATH_QUATERNION_HPP

#include <Dunjun/Math/Vector3.hpp>
#include <Dunjun/Math/Matrix4.hpp>
#include <Dunjun/Math/Angle.hpp>
#include <Dunjun/Math/Constants.hpp>

#include <ostream>

namespace Dunjun
{
struct Quaternion
{
	Quaternion();
	Quaternion(const Quaternion& q) = default;
	explicit Quaternion(f32 x, f32 y, f32 z, f32 w);
	explicit Quaternion(const Vector3& v, f32 s);

	inline const f32& operator[](usize index) const { return data[index]; }
	inline f32& operator[](usize index) { return data[index]; }

	Quaternion operator-() const;
	Quaternion operator+(const Quaternion& b) const;
	Quaternion operator-(const Quaternion& b) const;

	Quaternion operator*(const Quaternion& b) const;
	Quaternion operator*(f32 s) const;
	Quaternion operator/(f32 s) const;

	bool operator==(const Quaternion& b) const;
	bool operator!=(const Quaternion& b) const;

	const Vector3 vector() const;
	Vector3& vector();

	f32 scalar() const;
	f32& scalar();

	f32 lengthSquared() const;

	f32 length() const;

	// NOTE(bill): GLSL, vec4 xyzw
	union
	{
		f32 data[4];
		struct
		{
			f32 x, y, z, w;
		};
	};
};

inline Quaternion operator*(f32 s, const Quaternion& q) { return q * s; }

f32 dot(const Quaternion& a, const Quaternion& b);
Quaternion cross(const Quaternion& a, const Quaternion& b);

Quaternion normalize(const Quaternion& q);

Quaternion conjugate(const Quaternion& q);
Quaternion inverse(const Quaternion& q);

// NOTE(bill): Rotate v by q
Vector3 operator*(const Quaternion& q, const Vector3& v);

inline std::ostream& operator<<(std::ostream& os, const Quaternion& q)
{
	os << "Quaternion(";
	for (usize i = 0; i < 4; i++)
	{
		os << q[i];
		if (i < 3)
			os << ", ";
	}
	os << ")";

	return os;
}

Radian angle(const Quaternion& q);
Vector3 axis(const Quaternion& q);
Quaternion angleAxis(const Radian& angle, const Vector3& axis);

// TODO(bill): rotate quaternion by an angle around a given axis
// Quaternion rotate(const Quaternion& q, const Radian& angle, cosnt Vector3&
// axis);

Matrix4 quaternionToMatrix4(const Quaternion& q);
// NOTE(bill): Assumes matrix is only a rotational matrix and has no skew
//             applied
Quaternion matrix4ToQuaternion(const Matrix4& m);

struct EulerAngles
{
	Radian pitch;
	Radian yaw;
	Radian roll;
};

inline Radian roll(const Quaternion& q);
inline Radian pitch(const Quaternion& q);
inline Radian yaw(const Quaternion& q);

inline EulerAngles quaternionToEulerAngles(const Quaternion& q);
} // namespace Dunjun

#endif
