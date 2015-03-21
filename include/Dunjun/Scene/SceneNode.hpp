#ifndef DUNJUN_SCENE_SCENENODE_HPP
#define DUNJUN_SCENE_SCENENODE_HPP

#include <Dunjun/Common.hpp>
#include <Dunjun/ReadOnly.hpp>
#include <Dunjun/Transform.hpp>
#include <Dunjun/NonCopyable.hpp>
#include <Dunjun/Renderer.hpp>
#include <Dunjun/Drawable.hpp>

#include <Dunjun/Scene/NodeComponent.hpp>

#include <array>
#include <bitset>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <deque>
#include <typeinfo>
#include <typeindex>

namespace Dunjun
{
using ComponentID = usize;

namespace Impl
{
inline ComponentID getUniqueComponentID()
{
	LOCAL_PERSIST ComponentID lastID = 0;
	return lastID++;
}
} // namespace Impl

template <class ComponentType>
inline ComponentID getComponentTypeID()
{
	static_assert(std::is_base_of<NodeComponent, ComponentType>::value,
	              "ComponentType must inherit from NodeComponent.");

	LOCAL_PERSIST ComponentID typeID = Impl::getUniqueComponentID();
	return typeID;
}

class SceneNode : public Drawable, private NonCopyable
{
public:
	using UPtr = std::unique_ptr<SceneNode>;
	using GroupedComponentMap =
	    std::map<std::type_index, std::vector<NodeComponent::UPtr>>;

	GLOBAL const usize MaxComponents = 32;
	using ComponentBitset = std::bitset<MaxComponents>;
	using ComponentArray = std::array<NodeComponent*, MaxComponents>;

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

	template <class ComponentType, class... Args>
	ComponentType& addComponent(Args&&... args)
	{
		assert(!hasComponent<ComponentType>());

		ComponentType* component(
			new ComponentType(std::forward<Args>(args)...));
		component->parent = this;
		m_components.push_back(std::unique_ptr<NodeComponent>(component));

		m_componentArray[getComponentTypeID<ComponentType>()] = component;
		m_componentBitset[getComponentTypeID<ComponentType>()] = true;

		return *component;
	}

	template <class ComponentType>
	bool hasComponent() const
	{
		return m_componentBitset[getComponentTypeID<ComponentType>()];
	}

	template <class ComponentType>
	NodeComponent& getComponent()
	{
		assert(hasComponent<ComponentType>());
		auto ptr = m_componentArray[getComponentTypeID<ComponentType>()];
		return *reinterpret_cast<ComponentType*>(ptr);
	}


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

	std::vector<NodeComponent::UPtr> m_components;
	ComponentArray m_componentArray;
	ComponentBitset m_componentBitset;
};
} // namespace Dunjun

#endif
