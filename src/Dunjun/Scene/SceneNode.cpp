#include <Dunjun/Scene/SceneNode.hpp>

#include <algorithm>

namespace Dunjun
{
SceneNode::SceneNode()
: m_children()
, name("")
, transform()
, parent(nullptr)
{
}

SceneNode& SceneNode::attachChild(UPtr child)
{
	child->parent = this;
	m_children.push_back(std::move(child));

	return *this;
}

SceneNode::UPtr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(m_children.begin(),
	                          m_children.end(),
	                          [&node](UPtr& child)
	                          {
		                          return child.get() == &node;
		                      });

	if (found != m_children.end()) // Child was found
	{
		UPtr result = std::move(*found);

		result->parent = nullptr;
		m_children.erase(found);

		return result;
	}

	// No child was found
	return nullptr;
}

SceneNode* SceneNode::findChildByName(const std::string& name) const
{
	for (const UPtr& child : m_children)
	{
		if (child->name == name)
			return child.get();
	}

	return nullptr;
}

Transform SceneNode::getGlobalTransform() const
{
	Transform result;

	for (const SceneNode* node = this; node != nullptr; node = node->parent)
		result *= node->transform;

	return result;
}

void SceneNode::onStart()
{
	onStartCurrent();
	onStartChildren();
	for (auto& group : m_groupedComponents)
	{
		for (auto& component : group.second)
			component->onStart();
	}
}

void SceneNode::update(f32 dt)
{
	updateCurrent(dt);
	updateChildren(dt);
	for (auto& group : m_groupedComponents)
	{
		for (auto& component : group.second)
			component->update(dt);
	}
}

void SceneNode::draw(Renderer& renderer, Transform t)
{
	t *= this->transform;

	drawCurrent(renderer, t);
	drawChildren(renderer, t);
	for (auto& group : m_groupedComponents)
	{
		for (auto& component : group.second)
			component->draw(renderer, t);
	}
}

void SceneNode::onStartCurrent()
{
	// Do nothing by default
}

void SceneNode::onStartChildren()
{
	for (UPtr& child : m_children)
		child->onStart();
}

void SceneNode::updateCurrent(f32 dt)
{
	// Do nothing by default
}

void SceneNode::updateChildren(f32 dt)
{
	for (UPtr& child : m_children)
		child->update(dt);
}

void SceneNode::drawCurrent(Renderer& renderer, Transform t)
{
	// Do nothing by default
}

void SceneNode::drawChildren(Renderer& renderer, Transform t)
{
	for (UPtr& child : m_children)
		child->draw(renderer, t);
}

SceneNode* SceneNode::addComponent(NodeComponent* component)
{
	component->parent = this;

	const std::type_index id(typeid(*component));

	m_groupedComponents[id].push_back(component);

	return this;
}

} // namespace Dunjun
