#include "syScene.h"

namespace sy
{
	Scene::Scene()
	{
		mLayers.resize((int)eLayerType::End); // End -1개 만 생성해야하는거 아닐까?
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{
		mLayers[(int)eLayerType::Player].AddGameObject();
		std::wstring str = L"Player Layer";
		mLayers[(int)eLayerType::Player].SetName(str);
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
}