#include <Dunjun/Scene/FaceCamera.hpp>

#include <Dunjun/Scene/SceneNode.hpp>

#include <Dunjun/Math.hpp>

namespace Dunjun
{
void FaceCamera::update(Time dt)
{
	Vector3 pos = parent->getGlobalTransform().position;
	Vector3 camPos = camera->transform.position;

	parent->transform.orientation = conjugate(Math::lookAt<Quaternion>(camPos, pos, up));
}
} // namespace Dunjun