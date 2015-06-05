#ifndef DUNJUN_GRAPHICS_CAMERA_HPP
#define DUNJUN_GRAPHICS_CAMERA_HPP

#include <Dunjun/System/Types.hpp>
#include <Dunjun/Graphics/Transform.hpp>

namespace Dunjun
{
enum class ProjectionType
{
	Perspective,
	InfinitePerspective,
	Orthographic,
};

struct Camera
{
	Camera();
	Camera(const Camera& other) = default;

	void lookAt(const Vector3& position, const Vector3& up = {0, 1, 0});

	// NOTE(bill): +ve == ccw => +ve yaw == face up, +ve pitch == face left
	// Using Right-Handed Coordinate System
	void offsetOrientation(const Radian& yaw, const Radian& pitch);

	Vector3 forward() const;
	Vector3 backward() const;

	Vector3 right() const;
	Vector3 left() const;

	Vector3 up() const;
	Vector3 down() const;

	Matrix4 getMatrix() const;
	Matrix4 getProjection() const;
	Matrix4 getView() const;

	Transform transform;
	Radian fieldOfView;
	f32 orthoScale;
	f32 nearPlane;
	f32 farPlane;
	f32 viewportAspectRatio;
	ProjectionType projectionType;
};
} // namespace Dunjun

#endif
