#include <Dunjun/Camera.hpp>

namespace Dunjun
{
	Camera::Camera()
		: transform()
		, fieldOfView(Degree(50))
		, nearPlane(0.1f)
		, farPlane(256.0f)
		, viewportAspectRatio(4.0f / 3.0f)
		, projectionType(ProjectionType::Perspective)
	{
	}

	void Camera::lookAt(const Vector3& position)
	{
		const Vector3& pos = transform.position;

		if (length(pos - position) <= Constants::EPSILON)
			return; // ignore as you cannot look at where you are!

		if (fabs(dot(pos, {0, 1, 0}) - 1.0f) <= Constants::EPSILON)
		{
			std::cerr << "Camera::lookAt - viewDirection and Up vector are colinear.\n";
			return;
		}

		Matrix4 mat = Dunjun::lookAt(pos, position, {0, 1, 0});
		
		// TODO(bill): quaternionToMatrix4
		transform.orientation = quaternionToMatrix4(mat);
	
	}

	void Camera::offsetOrientation(const Radian& yaw, const Radian& pitch)
	{

	}

	Vector3 Camera::forward() const
	{

	}

	Vector3 Camera::backward() const
	{

	}

	Vector3 Camera::right() const
	{

	}

	Vector3 Camera::left() const
	{

	}

	Vector3 Camera::up() const
	{

	}

	Vector3 Camera::down() const
	{

	}

	Matrix4 Camera::getMatrix() const
	{

	}

	Matrix4 Camera::getProjection() const
	{

	}

	Matrix4 Camera::getView() const
	{

	}
} // namespace Dunjun
