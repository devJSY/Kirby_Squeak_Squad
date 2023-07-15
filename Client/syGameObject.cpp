#include "syGameObject.h"
#include "syTransform.h"
#include "sySpriteRenderer.h"

namespace sy
{
	GameObject::GameObject()
	{
		AddComponent<Transform>();
		Transform* tr = GetComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			if (nullptr != comp)
			{
				delete comp;
				comp = nullptr;
			}
		}

		mComponents.clear();
	}

	void GameObject::Initialize()
	{
		for (Component* comp : mComponents)
		{
			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			comp->Update();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* comp : mComponents)
		{
			comp->Render(hdc);
		}
	}
}