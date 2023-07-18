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
		// �ش� ���̾� ���� ������Ʈ�� ����
		mLayers[(int)type].DeleteObjects();
	}

	void Scene::DeleteAllLayer()
	{
		// ��� ���̾��� ������Ʈ ����
		for (size_t i = 0; i < mLayers.size(); i++)
		{
			DeleteLayer((eLayerType)i);
		}
	}
}