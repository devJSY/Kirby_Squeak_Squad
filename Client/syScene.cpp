#include "syScene.h"
#include "syObject.h"
#include "syDefaultKirby.h"
#include "sySceneManager.h"

namespace sy
{
	Scene::Scene()
	{
		mLayers.resize((int)eLayerType::End); 
	}

	Scene::~Scene()
	{
		mLayers.clear();
	}

	void Scene::Initialize()
	{
		for (Layer& layer : mLayers)
		{
			layer.Initialize();
		}
	}

	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (Layer& layer : mLayers)
		{
			layer.Render(hdc);
		}
	}

	// 전달받은 오브젝트를 현재씬에서 지우고 인자로 들어온씬에 전달하는 함수
	void Scene::PassGameObject(const std::wstring& name, eLayerType type, GameObject* gameObj)
	{
		Scene* nextScene = SceneManager::GetScene(name);
		// 다음씬에 오브젝트를 넣는다
		nextScene->AddGameObject(type, gameObj);
		// 현재씬에서 오브젝트를 제외한다 (객체 삭제 X)
		RemoveGameObject(type, gameObj);		
	}

	void Scene::DeleteLayer(eLayerType type)
	{
		// 해당 레이어 안의 오브젝트를 삭제
		mLayers[(int)type].DeleteObjects();
	}

	void Scene::DeleteAllLayer()
	{
		// 모든 레이어의 오브젝트 삭제
		for (size_t i = 0; i < mLayers.size(); i++)
		{
			DeleteLayer((eLayerType)i);
		}
	}
}