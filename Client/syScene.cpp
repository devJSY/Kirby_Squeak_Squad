#include "syScene.h"

namespace sy
{
	Scene::Scene()
	{
		mLayers.resize((int)eLayerType::End); // End -1�� �� �����ؾ��ϴ°� �ƴұ�?
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