#include "syLayer.h"

namespace sy
{
	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (nullptr != obj)
			{
				delete obj;
				obj = nullptr;
			}
		}

		mGameObjects.clear();
	}

	void Layer::Initialize()
	{
		for (GameObject* obj : mGameObjects)
		{
			obj->Initialize();
		}
	}

	void Layer::Update()
	{
		for (GameObject* obj : mGameObjects)
		{
			obj->Update();
		}
	}

	void Layer::Render(HDC hdc)
	{
		for (GameObject* obj : mGameObjects)
		{
			obj->Render(hdc);
		}
	}

	void Layer::RemoveGameObject(GameObject* gameObj)
	{
		// mGameObjects ������ �ش� ������Ʈ�� iterator �� ã�ƿ´�
		auto it = find(mGameObjects.begin(), mGameObjects.end(), gameObj);
		// mGameObjects���� ���� �ش� ������Ʈ�� �����Ѵ�
		mGameObjects.erase(it);
	}

	void Layer::DeleteObjects()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (nullptr != obj)
			{
				delete obj;
				obj = nullptr;
			}
		}

		mGameObjects.clear();
	}
}