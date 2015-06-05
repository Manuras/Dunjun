#ifndef DUNJUN_SCENE_SCENENODE_HPP
#define DUNJUN_SCENE_SCENENODE_HPP

#include <Dunjun/Common.hpp>
#include <Dunjun/Graphics/Transform.hpp>
#include <Dunjun/System/NonCopyable.hpp>
#include <Dunjun/System/Time.hpp>

#include <Dunjun/Scene/SceneRenderer.hpp>

#include <Dunjun/Scene/NodeComponent.hpp>

#include <algorithm>
#include <array>
#include <bitset>
#include <deque>
#include <memory>
#include <string>

namespace Dunjun
{
using ComponentID = usize;

namespace
{
INTERNAL inline ComponentID getUniqueComponentID()
{
	LOCAL_PERSIST ComponentID lastID{0};
	return lastID++;
}
} // namespace (anonymous)

template <typename ComponentType>
inline ComponentID getComponentTypeID()
{
	static_assert(std::is_base_of<NodeComponent, ComponentType>::value,
	              "ComponentType must inherit from NodeComponent.");

	LOCAL_PERSIST ComponentID typeID{getUniqueComponentID()};
	return typeID;
}

class SceneNode : private NonCopyable
{
public:
	using UPtr = std::unique_ptr<SceneNode>;

	GLOBAL const usize MaxComponents{32};
	using ComponentBitset = std::bitset<MaxComponents>;
	using ComponentArray = std::array<NodeComponent*, MaxComponents>;
	using Id = u64; // There could be billions of them, even old ones!

	explicit SceneNode();

	virtual ~SceneNode() {}

	SceneNode& attachChild(UPtr&& child);
	UPtr detachChild(const SceneNode& node);

	SceneNode* findChildById(usize id) const;
	SceneNode* findChildByName(const std::string& name) const;

	Transform getGlobalTransform() const;

	void onStart();
	void update(Time dt);

	template <typename ComponentType, typename... Args>
	ComponentType& addComponent(Args&&... args)
	{
		static_assert(std::is_base_of<NodeComponent, ComponentType>::value,
		              "ComponentType must inherit from NodeComponent.");
		assert(!hasComponent<ComponentType>() &&
		       "SceneNode::addComponent component of that type already exists.");

		ComponentType* component{
		    new ComponentType{std::forward<Args>(args)...}};
		component->m_parent = this;
		m_components.emplace_back(std::unique_ptr<NodeComponent>{component});

		m_componentArray[getComponentTypeID<ComponentType>()] = component;
		m_componentBitset[getComponentTypeID<ComponentType>()] = true;

		return *component;
	}

	template <typename ComponentType>
	bool hasComponent() const
	{
		static_assert(std::is_base_of<NodeComponent, ComponentType>::value,
		              "ComponentType must inherit from NodeComponent.");

		return m_componentBitset[getComponentTypeID<ComponentType>()];
	}

	template <typename ComponentType>
	ComponentType& getComponent()
	{
		static_assert(std::is_base_of<NodeComponent, ComponentType>::value,
		              "ComponentType must inherit from NodeComponent.");

		assert(hasComponent<ComponentType>() &&
		       "SceneNode::getComponent component not in this SceneNode.");
		auto ptr = m_componentArray[getComponentTypeID<ComponentType>()];
		return *reinterpret_cast<ComponentType*>(ptr);
	}

	const SceneNode* getParent() const { return m_parent; }

	const Id id;
	std::string name;
	Transform transform{};
	bool visible{true};

protected:
	friend class SceneRenderer;

	void draw(SceneRenderer& renderer, Transform t = Transform{}) const;

	virtual void onStartCurrent();
	void onStartChildren();

	virtual void updateCurrent(Time dt);
	void updateChildren(Time dt);

	virtual void drawCurrent(SceneRenderer& renderer, Transform t) const;
	void drawChildren(SceneRenderer& renderer, Transform t) const;

	SceneNode* m_parent{nullptr};
	std::deque<UPtr> m_children{};

	std::deque<NodeComponent::UPtr> m_components{};
	ComponentArray m_componentArray{};
	ComponentBitset m_componentBitset{};
};
} // namespace Dunjun

#endif
