#include "syEffects.h"

namespace sy
{
	Effects::Effects()
		: mOwner(nullptr)
		, mAnimator(nullptr)
		, mDir(eDirection::RIGHT)
	{
		mAnimator = AddComponent<Animator>();
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