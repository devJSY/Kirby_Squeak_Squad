#include "syGameObject.h"
#include "syTransform.h"
#include "sySpriteRenderer.h"

namespace sy
{
	GameObject::GameObject()
	{
		AddComponent<Transform>();
		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(Vector2(100.f, 100.f));
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
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