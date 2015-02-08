#ifndef DUNJUN_MATH_VECTOR3_HPP
#define DUNJUN_MATH_VECTOR3_HPP

#include <Dunjun/Types.hpp>

namespace Dunjun
{
struct Vector3
{
	Vector3()
	: x(0)
	, y(0)
	, z(0)
	{
	}

	explicit Vector3(f32 xyz)
	: x(xyz)
	, y(xyz)
	, z(xyz)
	{
	}

	Vector3(f32 x, f32 y, f32 z)
	: x(x)
	, y(y)
	, z(z)
	{
	}

	Vector3(f32 xyz[3])
	: x(xyz[0])
	, y(xyz[1])
	, z(xyz[2])
	{
	}

	f32& operator[](usize index) { return data[index]; }
	const f32& operator[](usize index) const { return data[index]; }

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
} // namespace Dunjun

#endif
