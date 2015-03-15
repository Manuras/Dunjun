#ifndef DUNJUN_TRANSFORM_HPP
#define DUNJUN_TRANSFORM_HPP

#include <Dunjun/Math/Vector3.hpp>
#include <Dunjun/Math/Quaternion.hpp>
#include <Dunjun/Math/Matrix4.hpp>

namespace Dunjun
{
struct Transform
{
	Vector3 position = {0, 0, 0};
	Quaternion orientation = Quaternion();
	Vector3 scale = {1, 1, 1};
};

// World = Parent * Local
Transform operator*(const Transform& ps, const Transform& ls);
Transform& operator*=(Transform& ps, const Transform& ls);
// Local = World / Parent
Transform operator/(const Transform& ws, const Transform& ps);
Transform& operator/=(Transform& ws, const Transform& ps);

Transform inverse(const Transform& t);
Matrix4 transformMatrix4(const Transform& t);
} // namespace Dunjun
#endif
