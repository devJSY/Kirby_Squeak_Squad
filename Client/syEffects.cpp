#include "syEffects.h"
#include "syAnimator.h"
#include "syCollider.h"

namespace sy
{
	Effects::Effects(GameObject* owner)
		: mOwner(owner)
	{
		AddComponent<Animator>();
	}

	Effects::~Effects()
	{
	}

	void Effects::Initialize()
	{
		GameObject::Initialize();
	}

	void Effects::Update()
	{
		GameObject::Update();
	}

	void Effects::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}