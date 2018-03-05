#pragma once
#include "Resource.h"
#include "Core\Subsystem.h"

class Resource;

class ResourceManager : public Subsystem
{
	FLUX_OBJECT(ResourceManager, Subsystem)

public:
	ResourceManager(Context* pContext);
	~ResourceManager();

	template <typename T, typename ...Args>
	T* Load(const std::string& filePath, Args... args)
	{
		auto pIt = m_Resources.find(filePath);
		if (pIt != m_Resources.end())
			return (T*)(pIt->second);

		Resource* pResource = new T(m_pContext, args...);
		if (!LoadResourcePrivate(pResource, filePath))
		{
			delete pResource;
			return nullptr;
		}
		m_Resources[filePath] = pResource;
		return (T*)pResource;
	}

	bool Reload(const std::string& filePath)
	{
		auto pIt = m_Resources.find(filePath);
		if (pIt == m_Resources.end())
			return nullptr;
		return LoadResourcePrivate(pIt->second, filePath);
	}

	std::vector<std::pair<std::string, Resource*>> GetResourcesOfType(StringHash type);

private:
	bool LoadResourcePrivate(Resource* pResource, const std::string& filePath);
	std::map<std::string, Resource*> m_Resources;
};