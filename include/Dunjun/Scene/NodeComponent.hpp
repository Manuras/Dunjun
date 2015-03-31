#ifndef DUNJUN_SCENE_NODECOMPONENT_HPP
#define DUNJUN_SCENE_NODECOMPONENT_HPP

#include <Dunjun/NonCopyable.hpp>
#include <Dunjun/Types.hpp>
#include <Dunjun/Common.hpp>
#include <Dunjun/Transform.hpp>
#include <Dunjun/Scene/SceneRenderer.hpp>

namespace Dunjun
{
class SceneNode;
class NodeComponent : private NonCopyable
{
public:
	using UPtr = std::unique_ptr<NodeComponent>;

	NodeComponent() = default;

	virtual ~NodeComponent() {}

	virtual void onStart() {}
	virtual void update(f32 dt) {}
	virtual void draw(SceneRenderer& renderer, Transform t) const {}

	SceneNode* parent = nullptr;

private:
	friend class SceneNode;
};
} // namespace Dunjun

#endif
