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

	void Scene::ShowSceneName(HDC hdc, std::wstring& name, const wchar_t* ChangeKey)
	{	
		// Scene ¿Ã∏ß ∑ª¥ı∏µ
		wchar_t szName[50];
		wcscpy_s(szName, name.c_str());

		swprintf_s(szName, 50, L"%s", szName);
		int strLen = (int)wcsnlen_s(szName, 50);

		TextOut(hdc, 10, 10, szName, strLen);

		// Change Key ∑ª¥ı∏µ
		wchar_t szKey[50];
		swprintf_s(szKey, 50, L"%s", ChangeKey);
		strLen = (int)wcsnlen_s(szKey, 50);

		TextOut(hdc, 10, 50, szKey, strLen);
	}
}