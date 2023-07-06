#pragma once
#include "syScene.h"
#include "syGameObject.h"
#include "sySceneManager.h"

namespace sy::object
{
	template <typename T>
	static __forceinline T* Instantiate(eLayerType type)
	{
		T* gameObject = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(type, gameObject);
		return gameObject;
	}
}