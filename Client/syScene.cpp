#include "syScene.h"
#include "syObject.h"
#include "syDefaultKirby.h"

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