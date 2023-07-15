#pragma once
#include "syResource.h"

namespace sy
{
	class ResourceManager
	{
	private:
		// 객체 생성 차단
		ResourceManager();
		~ResourceManager() {};

	public:
		static void Release();

		template <typename T>
		static T* Find(const std::wstring& name)
		{
			auto iter = mResources.find(name);

			if (iter == mResources.end())
				return nullptr;

			return dynamic_cast<T*>(iter->second);
		}

		template <typename T>
		static T* Load(const std::wstring& name, const std::wstring& path)
		{
			T* resource = ResourceManager::Find<T>(name);

			// 이미 저장되어있는 리소스면 바로 꺼내온 리소스를 리턴
			if (resource != nullptr)
				return resource;

			resource = new T();
			if (FAILED(resource->Load(path)))
			{
				MessageBox(nullptr, L"Resource Load Failed!", L"Error", MB_OK);
				delete resource;
				return nullptr;
			}

			resource->SetName(name);
			resource->SetPath(path);
			mResources.insert(make_pair(name, resource));

			return resource;
		}

		template <typename T>
		static void Insert(const std::wstring& name, T* resource)
		{
			resource->SetName(name);
			mResources.insert(std::make_pair(name, resource));
		}

	private:
		static std::map<std::wstring, Resource*> mResources;
	};
}
