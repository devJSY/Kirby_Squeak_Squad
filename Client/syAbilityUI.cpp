#include "syAbilityUI.h"
#include "syTexture.h"
#include "syAnimator.h"
#include "syResourceManager.h"

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
		Animator* pAni = AddComponent<Animator>();

		Texture* tex = ResourceManager::Load<Texture>(L"Ability_UI", L"..\\Resources\\UI\\Ability_UI.bmp");

		pAni->CreateAnimation(tex, L"Ability_UI_Normal", Vector2::Zero, Vector2(40.f, 40.f), Vector2(40.f, 0.f), 1.f, 1);
		pAni->CreateAnimation(tex, L"Ability_UI_Fire", Vector2(40.f, 0), Vector2(40.f, 40.f), Vector2(40.f, 0.f), 1.f, 1);
		pAni->CreateAnimation(tex, L"Ability_UI_Ice", Vector2(80.f, 0), Vector2(40.f, 40.f), Vector2(40.f, 0.f), 1.f, 1);
		pAni->CreateAnimation(tex, L"Ability_UI_Cutter", Vector2(120.f, 0), Vector2(40.f, 40.f), Vector2(40.f, 0.f), 1.f, 1);
		pAni->CreateAnimation(tex, L"Ability_UI_Tornado", Vector2(160.f, 0), Vector2(40.f, 40.f), Vector2(40.f, 0.f), 1.f, 1);
		pAni->CreateAnimation(tex, L"Ability_UI_Ninja", Vector2(200.f, 0), Vector2(40.f, 40.f), Vector2(40.f, 0.f), 1.f, 1);

		pAni->PlayAnimation(L"Ability_UI_Normal", false);
		pAni->SetAffectedCamera(false);

		UI::Initialize();
	}

	void AbilityUI::Update()
	{
		UI::Update();
	}

	void AbilityUI::Render(HDC hdc)
	{
		UI::Render(hdc);
	}
}