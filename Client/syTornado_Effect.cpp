#include "syTornado_Effect.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syTransform.h"

namespace sy
{
	Tornado_Effect::Tornado_Effect(GameObject* owner)
		: Effects(owner)
		, mAnimator(nullptr)
	{
		GetComponent<Transform>()->SetPosition(owner->GetComponent<Transform>()->GetPosition());

		// 텍스쳐 로드
		Texture* Tornado_Skill_End_Tex = ResourceManager::Load<Texture>(L"Tornado_Skill_End_Tex", L"..\\Resources\\Effect\\Tornado_Skill_End.bmp");

		mAnimator = GetComponent<Animator>();

		mAnimator->CreateAnimation(Tornado_Skill_End_Tex, L"Tornado_Skill_End", Vector2(0.f, 0.f), Vector2(100.f, 50.f), Vector2(100.f, 0.f), 0.1f, 3);

		mAnimator->PlayAnimation(L"Tornado_Skill_End", false);
	}

	Tornado_Effect::~Tornado_Effect()
	{
	}

	void Tornado_Effect::Initialize()
	{
		Effects::Initialize();
	}

	void Tornado_Effect::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		Effects::Update();
	}

	void Tornado_Effect::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}
}