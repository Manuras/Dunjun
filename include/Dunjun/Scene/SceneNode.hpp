#ifndef DUNJUN_SCENE_SCENENODE_HPP
#define DUNJUN_SCENE_SCENENODE_HPP

#include <Dunjun/Common.hpp>
#include <Dunjun/ReadOnly.hpp>
#include <Dunjun/Transform.hpp>
#include <Dunjun/NonCopyable.hpp>
#include <Dunjun/Renderer.hpp>

#include <Dunjun/Scene/NodeComponent.hpp>

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <deque>
#include <typeinfo>
#include <typeindex>

namespace Dunjun
{
class SceneNode : private NonCopyable
{
public:
	using UPtr = std::unique_ptr<SceneNode>;
	using GroupedComponentMap =
	    std::map<std::type_index, std::vector<NodeComponent::UPtr>>;

	SceneNode();

	virtual ~SceneNode() {}

	SceneNode& attachChild(UPtr child);
	UPtr detachChild(const SceneNode& node);

	
	// NOTE(bill): Children of only this node
	// TODO(bill): Search all children and children of children
	SceneNode* findChildById(usize id) const;

	// NOTE(bill): Children of only this node
	// TODO(bill): Search all children and children of children
	SceneNode* findChildByName(const std::string& name) const;

	Transform getGlobalTransform() const;

	void onStart();
	void update(f32 dt);

	const usize id;
	std::string name;
	Transform transform;
	ReadOnly<SceneNode*, SceneNode> parent;
	bool visible = true;

protected:
	friend class Renderer;

	void draw(Renderer& renderer, Transform t = Transform()) const;

	virtual void onStartCurrent();
	void onStartChildren();

	virtual void updateCurrent(f32 dt);
	void updateChildren(f32 dt);

	virtual void drawCurrent(Renderer& renderer, Transform t) const;
	void drawChildren(Renderer& renderer, Transform t) const;

	std::deque<UPtr> m_children;

	// NOTE(bill): A GroupedComponentMap groups components of the same
	//             type together by std::type_index(...)
	GroupedComponentMap m_groupedComponents;

public:
	SceneNode* addComponent(NodeComponent::UPtr component);

	template <class Derived, class... Args>
	inline SceneNode* addComponent(Args&&... args)
	{
		return addComponent(make_unique<Derived>(args...));
	}

	inline void removeAllComponents()
	{
		for (auto& group : m_groupedComponents)
			group.second.clear();
		m_groupedComponents.clear();
	}

	template <class ComponentType>
	std::vector<NodeComponent::UPtr>* getComponents()
	{
		if (!std::is_base_of<NodeComponent, ComponentType>::vale)
			return nullptr;

		if (m_groupedComponents.size() == 0)
			return nullptr;

		const std::type_index id(typeid(ComponentType));

		for (auto& group : m_groupedComponents)
		{
			if (group.first == id)
				return &m_groupedComponents[id];
		}

		return nullptr;
	}

	// NOTE(bill): Return the first component of type ComponentType if the
	//             there is one attached, else nullptr if there isn't
	template <class ComponentType>
	NodeComponent* getComponent()
	{
		auto c = getComponents<ComponentType>();
		if (c)
			return std::static_pointer_cast<ComponentType>(c->at(0).get());

		return nullptr;
	}
};
} // namespace Dunjun

#endif
