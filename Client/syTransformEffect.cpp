#include "syTransformEffect.h"
#include "syAnimator.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syPlayer.h"
#include "syTransform.h"

namespace sy
{
	TransformEffect::TransformEffect(Player* owner)
		: Effects(owner)
		, mAnimator(nullptr)
	{
		GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		Texture* TransformEffect_Tex = ResourceManager::Load<Texture>(L"TransformEffect_Tex", L"..\\Resources\\Effect\\TransformEffect.bmp");

		mAnimator = GetComponent<Animator>();

		mAnimator->CreateAnimation(TransformEffect_Tex, L"TransformEffect", Vector2(0.f, 0.f), Vector2(100.f, 100.f), Vector2(100.f, 0.f), 0.06f, 11);
		mAnimator->PlayAnimation(L"TransformEffect", false);
	}

	TransformEffect::~TransformEffect()
	{
	}

	void TransformEffect::Initialize()
	{
		Effects::Initialize();
	}

	void TransformEffect::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		Effects::Update();
	}

	void TransformEffect::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}
}