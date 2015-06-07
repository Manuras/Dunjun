#include <Dunjun/Scene/SceneNode.hpp>

#include <algorithm>
#include <cstdio>

namespace Dunjun
{
namespace
{
INTERNAL inline SceneNode::Id getUniqueSceneNodeId()
{
	LOCAL_PERSIST SceneNode::Id lastId{0};
	return lastId++;
}
} // namespace (anonymous)

SceneNode::SceneNode()
: id{getUniqueSceneNodeId()}
, m_componentBitset{}
{
	name = stringFormat("node_%llu", id);
}

SceneNode& SceneNode::attachChild(UPtr&& child)
{
	child->m_parent = this;
	m_children.emplace_back(std::move(child));

	return *this;
}

SceneNode::UPtr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(std::begin(m_children),
	                          std::end(m_children),
	                          [&node](UPtr& child)
	                          {
		                          return child.get() == &node;
		                      });

	if (found != std::end(m_children)) // Child was found
	{
		UPtr result{std::move(*found)};

		result->m_parent = nullptr;
		m_children.erase(found);

		return result;
	}

	// No child was found
	return nullptr;
}

SceneNode* SceneNode::findChildById(usize id) const
{
	for (const UPtr& child : m_children)
{
		if (child->id == id)
			return child.get();
		// If not found, check its children
		SceneNode* subChild{child->findChildById(id)};
		if (subChild != nullptr)
			return subChild;
	}

	return nullptr;
}

SceneNode* SceneNode::findChildByName(const std::string& name) const
{
	for (const UPtr& child : m_children)
	{
		if (child->name == name)
			return child.get();
		// If not found, check its children
		SceneNode* subChild{child->findChildByName(name)};
		if (subChild != nullptr)
			return subChild;
	}

	return nullptr;
}

Transform SceneNode::getGlobalTransform() const
{
	Transform result;

	// Iterate upwards until parent node has no other parent node
	for (const SceneNode* node{this}; node != nullptr; node = node->getParent())
		result *= node->transform;

	return result;
}

void SceneNode::init()
{
	initCurrent();
	initChildren();
	for (auto& component : m_components)
		component->init();
}

void SceneNode::update(Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
	for (auto& component : m_components)
		component->update(dt);
}

void SceneNode::handleEvent(const Event& event)
{
	handleEventCurrent(event);
	handleEventChildren(event);
	for (auto& component : m_components)
		component->handleEvent(event);
}


void SceneNode::draw(SceneRenderer& renderer, Transform t) const
{
	if (!visible)
		return;

	t *= this->transform;

	drawCurrent(renderer, t);
	drawChildren(renderer, t);
	for (auto& component : m_components)
		component->draw(renderer, t);
}

void SceneNode::initCurrent()
{
	// Do nothing by default
}

void SceneNode::initChildren()
{
	for (UPtr& child : m_children)
		child->init();
}

void SceneNode::updateCurrent(Time dt)
{
	// Do nothing by default
}

void SceneNode::updateChildren(Time dt)
{
	for (UPtr& child : m_children)
		child->update(dt);
}


void SceneNode::handleEventCurrent(const Event& event)
{
	// Do nothing by default
}

void SceneNode::handleEventChildren(const Event& event)
{
	for (UPtr& child : m_children)
		child->handleEvent(event);
}

void SceneNode::drawCurrent(SceneRenderer& renderer, Transform t) const
{
	// Do nothing by default
}

void SceneNode::drawChildren(SceneRenderer& renderer, Transform t) const
{
	for (const UPtr& child : m_children)
		child->draw(renderer, t);
}
} // namespace Dunjun
