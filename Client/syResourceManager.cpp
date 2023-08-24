#include "syResourceManager.h"
#include "sySound.h"

namespace sy
{
	std::map<std::wstring, Resource*> ResourceManager::mResources = {};
	std::map<std::wstring, Sound*> ResourceManager::mSounds = {};

	ResourceManager::ResourceManager()
	{
	}

	void ResourceManager::Release()
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

	void ResourceManager::AllSoundStop()
	{
		for (auto iter : mSounds)
		{
			if (nullptr != iter.second)
			{
				iter.second->Stop(true);
			}
		}
	}
}