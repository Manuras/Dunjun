#ifndef DUNJUN_SCENE_SCENENODE_HPP
#define DUNJUN_SCENE_SCENENODE_HPP

#include <Dunjun/Common.hpp>
#include <Dunjun/ReadOnly.hpp>
#include <Dunjun/Transform.hpp>

#include <memory>
#include <string>
#include <vector>

namespace Dunjun
{
class SceneNode
{
public:
	using UPtr = std::unique_ptr<SceneNode>;

	SceneNode();

	virtual ~SceneNode() {}

	SceneNode& attachChild(UPtr child);
	UPtr detachChild(const SceneNode& node);

	// NOTE(bill): Children of only this node
	// TODO(bill): Search all children and children of children
	SceneNode* findChildByName(const std::string& name) const;

	Transform getGlobalTransform() const;

	void onStart();
	void update(f32 dt);
	virtual void draw(Transform t = Transform());


	std::string name;
	Transform transform;
	ReadOnly<SceneNode*, SceneNode> parent;

protected:
	virtual void onStartCurrent();
	void onStartChildren();

	virtual void updateCurrent(f32 dt);
	void updateChildren(f32 dt);

	virtual void drawCurrent(Transform t);
	void drawChildren(Transform t);

	std::vector<UPtr> m_children;

};
} // namespace Dunjun

#endif
