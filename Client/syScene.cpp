#include "syScene.h"
#include "syObject.h"
#include "syDefaultKirby.h"
#include "sySceneManager.h"
#include "syCamera.h"

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
		for (size_t i = 0; i < mLayers.size(); i++)
		{
			if (Camera::GetCurCamEffect() == CAM_EFFECT::Transformations)
			{
				if (i == (size_t)eLayerType::Player 
					|| i == (size_t)eLayerType::TransformEffect
					|| i == (size_t)eLayerType::UI
					|| i == (size_t)eLayerType::Inventory)
				{
					mLayers[i].Update();
				}
			}
			else
			{
				mLayers[i].Update();
			}
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (Layer& layer : mLayers)
		{
			layer.Render(hdc);
		}
	}

	// ���޹��� ������Ʈ�� ��������� ����� ���ڷ� ���¾��� �����ϴ� �Լ�
	void Scene::PassGameObject(const std::wstring& name, eLayerType type, GameObject* gameObj)
	{
		Scene* nextScene = SceneManager::GetScene(name);
		// �������� ������Ʈ�� �ִ´�
		nextScene->AddGameObject(type, gameObj);
		// ��������� ������Ʈ�� �����Ѵ� (��ü ���� X)
		RemoveGameObject(type, gameObj);		
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