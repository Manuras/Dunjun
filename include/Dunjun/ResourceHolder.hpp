#ifndef DUNJUN_RESOURCEHOLDER_HPP
#define DUNJUN_RESOURCEHOLDER_HPP

#include <algorithm>
#include <memory>
//#include <map>
#include <unordered_map>

#include <cassert>

namespace Dunjun
{
template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	using IdentifierType = Identifier;
	using ResourceType = Resource;
	using ResourceUPtr = std::unique_ptr<Resource>;

	void insert(Identifier id, ResourceUPtr resource)
	{
		auto inserted = m_resources.insert(std::make_pair(id, std::move(resource)));
		assert(inserted.second &&
		       "ResourceHolder resource not inserted"); // just incase
	}

	std::unique_ptr<Resource> erase(const Resource& resource)
	{
		auto found = std::find_if(std::begin(m_resources),
								  std::end(m_resources),
								  [&resource](ResourceUPtr& res)
		{
			return res.get();
		});

		if (found != std::end(m_resources))
		{
			auto result = std::move(*found);

			m_resources.erase(found);

			return result;
		}

		// Resource not found
		return nullptr;
	}


	std::unique_ptr<Resource> erase(Identifier id)
	{
		auto found = m_resources.find(id);

		if (found != std::end(m_resources))
		{
			auto result = std::move(*found);

			m_resources.erase(found);

			return result;
		}

		// Resource not found
		return nullptr;
	}

	bool exists(Identifier id)
	{
		auto found = m_resources.find(id);

		if (found != std::end(m_resources))
			return true;

		return false;
	}

	Resource& get(Identifier id)
	{
		auto found = m_resources.find(id);
		assert(found != std::end(m_resources) &&
		       "ResourceHolder::get resource not found!");

		return *found->second;
	}

	const Resource& get(Identifier id) const
	{
		auto found = m_resources.find(id);
		assert(found != std::end(m_resources) &&
		       "ResourceHolder::get resource not found!");

		return *found->second;
	}

protected:
	std::unordered_map<Identifier, ResourceUPtr> m_resources;
};
} // namespace Dunjun

#endif
