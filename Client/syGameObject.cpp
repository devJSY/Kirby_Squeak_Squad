#include "syGameObject.h"
#include "syTransform.h"
#include "sySpriteRenderer.h"

namespace sy
{
	GameObject::GameObject()
	{
		mComponents.push_back(new Transform());
		mComponents[0]->SetOwner(this);

		mComponents.push_back(new SpriteRenderer());
		mComponents[1]->SetOwner(this);
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