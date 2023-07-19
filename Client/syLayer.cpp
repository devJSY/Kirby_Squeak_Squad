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