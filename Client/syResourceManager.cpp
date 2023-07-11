#include "syResourceManager.h"

namespace sy
{
	std::map<std::wstring, Resource*> ResourceManager::mResources = {};

	ResourceManager::ResourceManager()
	{
	}
	ResourceManager::~ResourceManager()
	{
		for (auto iter : mResources)
		{
			if (nullptr != iter.second)
			{
				delete iter.second;
				iter.second = nullptr;
			}
		}

		mResources.clear();
	}
}