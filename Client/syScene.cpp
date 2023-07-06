#include "syScene.h"

namespace sy
{
	Scene::Scene()
	{
		mLayers.resize((int)eLayerType::End); 
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{
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

	void Scene::ShowSceneName(HDC hdc, std::wstring& str)
	{	
		wchar_t szFloat[50];
		wcscpy_s(szFloat, str.c_str());

		swprintf_s(szFloat, 50, L"%s", szFloat);
		int strLen = (int)wcsnlen_s(szFloat, 50);

		TextOut(hdc, 10, 10, szFloat, strLen);
	}
}