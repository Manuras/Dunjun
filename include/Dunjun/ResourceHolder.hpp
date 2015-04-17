#ifndef DUNJUN_RESOURCEHOLDER_HPP
#define DUNJUN_RESOURCEHOLDER_HPP

#include <algorithm>
#include <memory>
#include <map>

namespace Dunjun
{
template <class Resource, class Identifier>
class ResourceHolder
{
public:
	using IdentifierType = Identifier;
	using ResourceType = Resource;
	using ResourceUPtr = std::unique_ptr<Resource>;

	void insert(Identifier id, ResourceUPtr resource)
	{
		auto inserted = m_resources.insert(std::make_pair(id, std::move(resource)));
		//assert(inserted.second); // just incase
	}

	std::unique_ptr<Resource> erase(const Resource& resource)
	{
		auto found = std::find_if(m_resources.begin(),
								  m_resources.end(),
								  [&resource](ResourceUPtr& res)
		{
			return res.get();
		});

		if (found != m_resources.end())
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

		if (found != m_resources.end())
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

		if (found != m_resources.end())
			return true;

		return false;
	}

	Resource& get(Identifier id)
	{
		auto found = m_resources.find(id);
		assert(found != m_resources.end());

		return *found->second;
	}

	const Resource& get(Identifier id) const
	{
		auto found = m_resources.find(id);
		assert(found != m_resources.end());

		return *found->second;
	}

protected:
	std::map<Identifier, ResourceUPtr> m_resources;
};
} // namespace Dunjun

#endif
