#include "syAbilityUI.h"
#include "syTexture.h"
#include "syAnimator.h"
#include "syResourceManager.h"
#include "syPlayer.h"

namespace sy
{
	AbilityUI::AbilityUI()
	{
	}

	AbilityUI::~AbilityUI()
	{
	}

	void AbilityUI::Initialize()
	{
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

		// Owner �� ���¿� ���� ���� �ִϸ��̼� ����
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