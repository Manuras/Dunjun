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
	void insert(Identifier id, std::unique_ptr<Resource> resource)
	{
		auto inserted = m_resources.insert(std::make_pair(id, std::move(resource)));
		assert(inserted.second); // just incase
	}

	// TODO(bill): erase by Identifier
	std::unique_ptr<Resource> erase(const Resource& resource)
	{
		auto found = std::find_if(m_resources.begin(),
								  m_resources.end(),
								  [&resource](std::unique_ptr<Resource>& res)
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

	bool has(Identifier id)
	{
		auto found = std::find_if(m_resources.begin(),
								  m_resources.end(),
								  [&resource](std::unique_ptr<Resource>& res)
		{
			return res.get();
		});

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

private:
	std::map<Identifier, std::unique_ptr<Resource>> m_resources;
};
} // namespace Dunjun

#endif 
