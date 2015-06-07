#include <Dunjun/Graphics/Transform.hpp>

#include <Dunjun/Math/Functions/Transformation.hpp>

namespace Dunjun
{
// World = Parent * Local
Transform operator*(const Transform& ps, const Transform& ls)
{
	Transform ws;

	ws.position = ps.position + ps.orientation * (ps.scale * ls.position);
	ws.orientation = ps.orientation * ls.orientation;
	ws.scale = ps.scale * (ps.orientation * ls.scale);

	return ws;
}

Transform& operator*=(Transform& ps, const Transform& ls)
{
	ps = ps * ls;

	return ps;
}

// Local = World / Parent
Transform operator/(const Transform& ws, const Transform& ps)
{
	Transform ls;

	const Quaternion psConjugate{conjugate(ps.orientation)};

	ls.position = (psConjugate * (ws.position - ps.position)) / ps.scale;
	ls.orientation = psConjugate * ws.orientation;
	ls.scale = psConjugate * (ws.scale / ps.scale);

	return ls;
}

Transform& operator/=(Transform& ws, const Transform& ps)
{
	ws = ws / ps;

	return ws;
}

Vector3 transformPoint(const Transform& transform, const Vector3& point)
{
	return (conjugate(transform.orientation) * (transform.position - point)) /
	       transform.scale;
}

Transform inverse(const Transform& t)
{
	const Quaternion invOrientation{conjugate(t.orientation)};

	Transform invTransform;

	invTransform.position = (invOrientation * -t.position) / t.scale;
	invTransform.orientation = invOrientation;
	invTransform.scale = invOrientation * (Vector3{1} / t.scale);

	return invTransform;
}

Matrix4 transformMatrix4(const Transform& t)
{
	return Math::translate(t.position) *        //
	       quaternionToMatrix4(t.orientation) * //
	       Math::scale(t.scale);                //
}
} // namespace Dunjun
