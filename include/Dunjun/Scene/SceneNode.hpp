#ifndef DUNJUN_SCENE_SCENENODE_HPP
#define DUNJUN_SCENE_SCENENODE_HPP

#include <Dunjun/Common.hpp>
#include <Dunjun/Transform.hpp>
#include <Dunjun/NonCopyable.hpp>
#include <Dunjun/Time.hpp>

#include <Dunjun/Scene/SceneRenderer.hpp>

#include <Dunjun/Scene/NodeComponent.hpp>

#include <array>
#include <bitset>
#include <memory>
#include <string>
#include <deque>

#include <algorithm>

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

class SceneNode : private NonCopyable
{
public:
	using UPtr = std::unique_ptr<SceneNode>;

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
	void update(Time dt);

	template <class ComponentType, class... Args>
	ComponentType& addComponent(Args&&... args)
	{
		assert(!hasComponent<ComponentType>());

		ComponentType* component{
		    new ComponentType{std::forward<Args>(args)...}};
		component->m_parent = this;
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
	ComponentType& getComponent()
	{
		assert(hasComponent<ComponentType>());
		auto ptr{m_componentArray[getComponentTypeID<ComponentType>()]};
		return *reinterpret_cast<ComponentType*>(ptr);
	}

	SceneNode* getParent() const { return m_parent; }

	using Id = u64;
	const Id id;
	std::string name;
	Transform transform;
	bool visible{true};

protected:
	friend class SceneRenderer;

	void draw(SceneRenderer& renderer, Transform t = Transform()) const;

	virtual void onStartCurrent();
	void onStartChildren();

	virtual void updateCurrent(Time dt);
	void updateChildren(Time dt);

	virtual void drawCurrent(SceneRenderer& renderer, Transform t) const;
	void drawChildren(SceneRenderer& renderer, Transform t) const;

	SceneNode* m_parent{nullptr};
	std::deque<UPtr> m_children;

	std::deque<NodeComponent::UPtr> m_components;
	ComponentArray m_componentArray;
	ComponentBitset m_componentBitset;
};
} // namespace Dunjun

#endif
