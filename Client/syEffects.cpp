#include "syEffects.h"

namespace sy
{
	Effects::Effects()
		: mOwner(nullptr)
		, mAnimator(nullptr)
	{
		mAnimator = AddComponent<Animator>();
		assert(mAnimator);
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