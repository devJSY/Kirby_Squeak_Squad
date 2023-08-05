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
		for (size_t i = 0; i < mGameObjects.size(); i++)
		{
			if (mGameObjects[i]->GetGameObjectState() == GameObject::eGameObjectState::Pause)
				continue;

			mGameObjects[i]->Initialize();
		}
	}

	void Layer::Update()
	{
		for (size_t i = 0; i < mGameObjects.size(); i++)
		{
			if (mGameObjects[i]->GetGameObjectState() == GameObject::eGameObjectState::Pause)
					continue;

			mGameObjects[i]->Update();
		}
	}

	void Layer::Render(HDC hdc)
	{
		for (size_t i = 0; i < mGameObjects.size(); i++)
		{
			if (mGameObjects[i]->GetGameObjectState() == GameObject::eGameObjectState::Pause)
				continue;

			mGameObjects[i]->Render(hdc);
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