#ifndef DUNJUN_CAMERA_HPP
#define DUNJUN_CAMERA_HPP

#include <Dunjun/Types.hpp>
#include <Dunjun/Transform.hpp>

namespace Dunjun
{
enum class ProjectionType
{
	Perspective,
	Orthographic,
};

struct Camera
{
	Camera();
	Camera(const Camera& other) = default;

	void lookAt(const Vector3& position);

	// TODO(bill): offsetOrientation
	void offsetOrientation(const Radian& yaw, const Radian& pitch);

	// TODO(bill): Camera Vector3 Directions
	Vector3 forward() const;
	Vector3 backward() const;

	Vector3 right() const;
	Vector3 left() const;

	Vector3 up() const;
	Vector3 down() const;

	// TODO(bill): Camera Matrices
	Matrix4 getMatrix() const;
	Matrix4 getProjection() const;
	Matrix4 getView() const;

	Transform transform;
	Radian fieldOfView;
	f32 nearPlane;
	f32 farPlane;
	f32 viewportAspectRatio;
	ProjectionType projectionType;
};
} // namespace Dunjun

#endif
