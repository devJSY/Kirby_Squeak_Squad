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

		// Dead상태인 오브젝트는 Layer에서 제외한다
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
		// mGameObjects 내에서 해당 오브젝트의 iterator 를 찾아온다
		std::vector<GameObject*>::iterator iter = find(mGameObjects.begin(), mGameObjects.end(), gameObj);
		// mGameObjects벡터 에서 해당 오브젝트가 존재한다면 제외한다
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