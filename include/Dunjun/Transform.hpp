#ifndef DUNJUN_TRANSFORM_HPP
#define DUNJUN_TRANSFORM_HPP

#include <Dunjun/Math.hpp>

namespace Dunjun
{
struct Transform
{
	Vector3 position = {0, 0, 0};
	Quaternion orientation = {0, 0, 0, 1};
	Vector3 scale = {1, 1, 1};

	// World = Parent * Local
	Transform operator*(const Transform& ls) const
	{
		const Transform& ps = *this;
		Transform ws;

		ws.position = ps.position + ps.orientation * (ps.scale * ls.position);
		ws.orientation = ps.orientation * ls.orientation;
		ws.scale = ps.scale * (ps.orientation * ls.scale);

		return ws;
	}
	// Local = World / Parent
	Transform operator/(const Transform& ps) const
	{
		const Transform& ws = *this;
		Transform ls;

		const Quaternion psConjugate = conjugate(ps.orientation);

		ls.position = (psConjugate * (ws.position - ps.position)) / ps.scale;
		ls.orientation = psConjugate * ws.orientation;
		ls.scale = psConjugate * (ws.scale / ps.scale);

		return ls;
	}
};

inline Transform inverse(const Transform& t)
{
	const Transform i;
	return i / t;
}

inline Matrix4 transformMatrix4(const Transform& t)
{
	return translate(t.position) * quaternionToMatrix4(t.orientation) * scale(t.scale);
}

} // namespace Dunjun
#endif
