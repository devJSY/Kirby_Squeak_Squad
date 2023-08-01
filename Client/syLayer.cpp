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
			if (obj->GetGameObjectState() == GameObject::eGameObjectState::Pause)
				continue;

			obj->Update();
		}
	}

	void Layer::Render(HDC hdc)
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj->GetGameObjectState() == GameObject::eGameObjectState::Pause)
				continue;

			obj->Render(hdc);
		}

		// Dead������ ������Ʈ�� Layer���� �����Ѵ�
		for (std::vector<GameObject*>::iterator iter = mGameObjects.begin()
			; iter != mGameObjects.end()
			; )
		{
			if ((*iter)->GetGameObjectState() == GameObject::eGameObjectState::Dead)
			{
				GameObject* obj = *iter;
				iter = mGameObjects.erase(iter);
				delete obj;
				obj = nullptr;
			}
			else
			{
				iter++;
			}
		}
	}

	void Layer::RemoveGameObject(GameObject* gameObj)
	{
		// mGameObjects ������ �ش� ������Ʈ�� iterator �� ã�ƿ´�
		std::vector<GameObject*>::iterator iter = find(mGameObjects.begin(), mGameObjects.end(), gameObj);
		// mGameObjects���� ���� �ش� ������Ʈ�� �����Ѵٸ� �����Ѵ�
		if (iter != mGameObjects.end())
			mGameObjects.erase(iter);			
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