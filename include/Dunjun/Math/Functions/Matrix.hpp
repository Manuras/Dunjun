#ifndef DUNJUN_MATH_FUNCTIONS_MATRIX_HPP
#define DUNJUN_MATH_FUNCTIONS_MATRIX_HPP

#include <Dunjun/Math/Vector3.hpp>
#include <Dunjun/Math/Matrix4.hpp>

#include <cmath>

namespace Dunjun
{
Matrix4 translate(const Vector3& v);
// Angle in Radians
Matrix4 rotate(f32 angle, const Vector3& v);
Matrix4 scale(const Vector3& v);
} // namespace Dunjun

#endif
