#include <Dunjun/Scene/FaceCamera.hpp>

#include <Dunjun/Scene/SceneNode.hpp>

#include <Dunjun/Math.hpp>

namespace Dunjun
{
void FaceCamera::update(f32 dt)
{

	Vector3 pos = parent->getGlobalTransform().position;
	Vector3 camPos = camera->transform.position;

	Matrix4 orienation = matrix4lookAt(camPos, pos, up);


	parent->transform.orientation = conjugate(matrix4ToQuaternion(orienation));
}
} // namespace Dunjun