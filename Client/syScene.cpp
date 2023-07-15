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

	void Scene::ShowSceneName(HDC hdc, std::wstring& name, const wchar_t* ChangeKey)
	{	
		// Scene 이름 렌더링
		wchar_t szName[50];
		wcscpy_s(szName, name.c_str());

		swprintf_s(szName, 50, L"%s", szName);
		int strLen = (int)wcsnlen_s(szName, 50);

		TextOut(hdc, 10, 10, szName, strLen);

		// Change Key 렌더링
		wchar_t szKey[50];
		swprintf_s(szKey, 50, L"%s", ChangeKey);
		strLen = (int)wcsnlen_s(szKey, 50);

		TextOut(hdc, 10, 50, szKey, strLen);
	}
}