#include "syAbilityUI.h"
#include "syTexture.h"
#include "syAnimator.h"
#include "syResourceManager.h"
#include "syPlayer.h"
#include "syTransform.h"
#include "syApplication.h"

namespace sy
{
	AbilityUI::AbilityUI()
		: mOwner(nullptr)
		, mAnimator(nullptr)
	{
	}

	AbilityUI::~AbilityUI()
	{
	}

	void AbilityUI::Initialize()
	{
		// AbilityUI 기본 위치 설정 
		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.x = 20.0f;
		vec.y -= 25.f;
		GetComponent<Transform>()->SetPosition(vec);

		mAnimator = AddComponent<Animator>();

		Texture* tex = ResourceManager::Load<Texture>(L"Ability_UI_Tex", L"..\\Resources\\UI\\Ability_UI.bmp");

		mAnimator->CreateAnimation(tex, L"Ability_UI_Normal", Vector2::Zero, Vector2(40.f, 40.f), Vector2(40.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(tex, L"Ability_UI_Fire", Vector2(40.f, 0), Vector2(40.f, 40.f), Vector2(40.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(tex, L"Ability_UI_Ice", Vector2(80.f, 0), Vector2(40.f, 40.f), Vector2(40.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(tex, L"Ability_UI_Cutter", Vector2(120.f, 0), Vector2(40.f, 40.f), Vector2(40.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(tex, L"Ability_UI_Tornado", Vector2(160.f, 0), Vector2(40.f, 40.f), Vector2(40.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(tex, L"Ability_UI_Ninja", Vector2(200.f, 0), Vector2(40.f, 40.f), Vector2(40.f, 0.f), 1.f, 1);

		mAnimator->PlayAnimation(L"Ability_UI_Normal", false);
		mAnimator->SetAffectedCamera(false);

		UI::Initialize();
	}

	void AbilityUI::Update()
	{
		UI::Update();

		// Owner 의 상태에 따라서 현재 애니메이션 설정
		if (nullptr != mOwner)
		{
			eAbilityType type = mOwner->GetAbilityType();
		
			if (type == eAbilityType::Normal)
				mAnimator->PlayAnimation(L"Ability_UI_Normal", false);		
			else if (type == eAbilityType::Fire)
				mAnimator->PlayAnimation(L"Ability_UI_Fire", false);		
			else if (type == eAbilityType::Ice)
				mAnimator->PlayAnimation(L"Ability_UI_Ice", false);		
			else if (type == eAbilityType::Cutter)
				mAnimator->PlayAnimation(L"Ability_UI_Cutter", false);	
			else if (type == eAbilityType::Tornado)
				mAnimator->PlayAnimation(L"Ability_UI_Tornado", false);		
			else if (type == eAbilityType::Ninja)
				mAnimator->PlayAnimation(L"Ability_UI_Ninja", false);		
		}
	}

	void AbilityUI::Render(HDC hdc)
	{
		UI::Render(hdc);
	}
}