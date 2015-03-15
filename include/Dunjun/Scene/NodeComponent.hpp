#ifndef DUNJUN_SCENE_NODECOMPONENT_HPP
#define DUNJUN_SCENE_NODECOMPONENT_HPP

#include <Dunjun/NonCopyable.hpp>
#include <Dunjun/Types.hpp>
#include <Dunjun/Common.hpp>
#include <Dunjun/Transform.hpp>

namespace Dunjun
{
class SceneNode;
class NodeComponent : private NonCopyable
{
public:
	NodeComponent() = default;

	virtual void onStart() {}
	virtual void update(f32 dt) {}
	virtual void draw(Transform t) {}

	SceneNode* parent = nullptr;

private:
	friend class SceneNode;
};
} // namespace Dunjun

#endif
