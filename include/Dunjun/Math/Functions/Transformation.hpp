#ifndef DUNJUN_MATH_FUNCTIONS_TRANSFORMATION_HPP
#define DUNJUN_MATH_FUNCTIONS_TRANSFORMATION_HPP

#include <Dunjun/Math/Vector3.hpp>
#include <Dunjun/Math/Matrix4.hpp>
#include <Dunjun/Math/Quaternion.hpp>

#include <Dunjun/Math/Angle.hpp>

#include <cmath>

namespace Dunjun
{
Matrix4 translate(const Vector3& v);
Matrix4 rotate(const Radian& angle, const Vector3& v);
Matrix4 scale(const Vector3& v);

Matrix4 ortho(f32 left, f32 right, f32 bottom, f32 top);
Matrix4 ortho(f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar);

Matrix4 perspective(const Radian& fovy, f32 aspect, f32 zNear, f32 zFar);
Matrix4 infinitePerspective(const Radian& fovy, f32 aspect, f32 zNear);

Matrix4 matrix4lookAt(const Vector3& eye,
                      const Vector3& center,
                      const Vector3& up);

Quaternion quaternionLookAt(const Vector3& eye,
                            const Vector3& center,
                            const Vector3& up);

} // namespace Dunjun

#endif
