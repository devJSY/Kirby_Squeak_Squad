#include "syEffects.h"
#include "syAnimator.h"
#include "syCollider.h"

namespace sy
{
	Effects::Effects()
		: mOwner(nullptr)
		, mAnimator(nullptr)
	{
		mAnimator = AddComponent<Animator>();
		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(10.f, 10.f));
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