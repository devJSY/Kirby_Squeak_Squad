#pragma once
#include "syScene.h"
#include "syGameObject.h"
#include "sySceneManager.h"

namespace sy::object
{
	template <typename T>
	static __forceinline T* Instantiate(eLayerType type)
	{
		// T 타입의 GameObject 생성 
		// 현재 씬에 type 레이어 에 생성한 오브젝트 추가
		T* gameObject = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(type, gameObject);
		return gameObject;
	}



}