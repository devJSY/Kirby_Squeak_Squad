#include "syAbilityUI.h"
#include "syTexture.h"
#include "syAnimator.h"
#include "syResourceManager.h"
#include "syPlayer.h"
#include "syTransform.h"
#include "syApplication.h"
#include "sySceneManager.h"

namespace sy
{
	AbilityUI::AbilityUI()
		: mIconAnimator(nullptr)
		, mNameAnimator(nullptr)
		, mNameBase(nullptr)
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
		vec.y -= 27.f;
		GetComponent<Transform>()->SetPosition(vec);

		mIconAnimator = AddComponent<Animator>();
		mNameBase = AddComponent<Animator>();
		mNameAnimator = AddComponent<Animator>();

		Texture* tex = ResourceManager::Load<Texture>(L"Ability_UI_Tex", L"..\\Resources\\UI\\Ability_UI.bmp");

		mIconAnimator->CreateAnimation(tex, L"Ability_UI_Normal", Vector2::Zero, Vector2(40.f, 26.f), Vector2(40.f, 0.f), 1.f, 1);
		mIconAnimator->CreateAnimation(tex, L"Ability_UI_Fire", Vector2(40.f, 0), Vector2(40.f, 26.f), Vector2(40.f, 0.f), 1.f, 1);
		mIconAnimator->CreateAnimation(tex, L"Ability_UI_Ice", Vector2(80.f, 0), Vector2(40.f, 26.f), Vector2(40.f, 0.f), 1.f, 1);
		mIconAnimator->CreateAnimation(tex, L"Ability_UI_Cutter", Vector2(120.f, 0), Vector2(40.f, 26.f), Vector2(40.f, 0.f), 1.f, 1);
		mIconAnimator->CreateAnimation(tex, L"Ability_UI_Tornado", Vector2(160.f, 0), Vector2(40.f, 26.f), Vector2(40.f, 0.f), 1.f, 1);
		mIconAnimator->CreateAnimation(tex, L"Ability_UI_Ninja", Vector2(200.f, 0), Vector2(40.f, 26.f), Vector2(40.f, 0.f), 1.f, 1);
		mIconAnimator->CreateAnimation(tex, L"Ability_UI_Wheel", Vector2(25.f, 80.f), Vector2(25.f, 26.f), Vector2(25.f, 0.f), 1.f, 1, Vector2(0.f, 1.f));

		Vector2 offset = Vector2(0.f, 20.f);

		mNameAnimator->CreateAnimation(tex, L"Ability_UI_Normal_Name",Vector2(0.f, 27.f), Vector2(40.f, 13.f), Vector2(40.f, 0.f), 1.f, 1, offset);
		mNameAnimator->CreateAnimation(tex, L"Ability_UI_Fire_Name", Vector2(40.f, 27.f), Vector2(40.f, 13.f), Vector2(40.f, 0.f), 1.f, 1, offset);
		mNameAnimator->CreateAnimation(tex, L"Ability_UI_Ice_Name", Vector2(80.f, 27.f), Vector2(40.f, 13.f), Vector2(40.f, 0.f), 1.f, 1, offset);
		mNameAnimator->CreateAnimation(tex, L"Ability_UI_Cutter_Name", Vector2(120.f, 27.f), Vector2(40.f, 13.f), Vector2(40.f, 0.f), 1.f, 1, offset);
		mNameAnimator->CreateAnimation(tex, L"Ability_UI_Tornado_Name", Vector2(160.f, 27.f), Vector2(40.f, 13.f), Vector2(40.f, 0.f), 1.f, 1, offset);
		mNameAnimator->CreateAnimation(tex, L"Ability_UI_Ninja_Name", Vector2(200.f, 27.f), Vector2(40.f, 13.f), Vector2(40.f, 0.f), 1.f, 1, offset);
		mNameAnimator->CreateAnimation(tex, L"Ability_UI_Wheel_Name", Vector2(35.f, 111.f), Vector2(28.f, 13.f), Vector2(28.f, 0.f), 1.f, 1, offset);
		mNameAnimator->SetBmpRGB(L"Ability_UI_Wheel_Name", 0,0,0);

		mNameBase->CreateAnimation(tex, L"NameBase", Vector2(241.f, 27.f), Vector2(40.f, 13.f), Vector2(40.f, 0.f), 1.f, 1, offset);

		mIconAnimator->PlayAnimation(L"Ability_UI_Normal", false);
		mNameBase->PlayAnimation(L"NameBase", false);
		mNameAnimator->PlayAnimation(L"Ability_UI_Normal_Name", false);
		mIconAnimator->SetAffectedCamera(false);
		mNameBase->SetAffectedCamera(false);
		mNameAnimator->SetAffectedCamera(false);

		UI::Initialize();
	}

	void AbilityUI::Update()
	{
		UI::Update();

		Player* player = SceneManager::GetPlayer();
		// Owner 의 상태에 따라서 현재 애니메이션 설정
		if (nullptr != player)
		{
			eAbilityType type = player->GetAbilityType();
		
			if (type == eAbilityType::Normal)
			{
				mIconAnimator->PlayAnimation(L"Ability_UI_Normal", false);
				mNameAnimator->PlayAnimation(L"Ability_UI_Normal_Name", false);
			}	
			else if (type == eAbilityType::Fire)
			{
				mIconAnimator->PlayAnimation(L"Ability_UI_Fire", false);
				mNameAnimator->PlayAnimation(L"Ability_UI_Fire_Name", false);
			}
			else if (type == eAbilityType::Ice)
			{
				mIconAnimator->PlayAnimation(L"Ability_UI_Ice", false);
				mNameAnimator->PlayAnimation(L"Ability_UI_Ice_Name", false);
			}
			else if (type == eAbilityType::Cutter)
			{
				mIconAnimator->PlayAnimation(L"Ability_UI_Cutter", false);
				mNameAnimator->PlayAnimation(L"Ability_UI_Cutter_Name", false);
			}
			else if (type == eAbilityType::Tornado)
			{
				mIconAnimator->PlayAnimation(L"Ability_UI_Tornado", false);
				mNameAnimator->PlayAnimation(L"Ability_UI_Tornado_Name", false);
			}
			else if (type == eAbilityType::Ninja)
			{
				mIconAnimator->PlayAnimation(L"Ability_UI_Ninja", false);
				mNameAnimator->PlayAnimation(L"Ability_UI_Ninja_Name", false);
			}
			else if (type == eAbilityType::Wheel)
			{
				mIconAnimator->PlayAnimation(L"Ability_UI_Wheel", false);
				mNameAnimator->PlayAnimation(L"Ability_UI_Wheel_Name", false);
			}
		}
	}

	void AbilityUI::Render(HDC hdc)
	{
		UI::Render(hdc);
	}
}