#include "syEnemyHPbarUI.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syTime.h"
#include "syEnemy.h"

namespace sy
{
	EnemyHPbarUI::EnemyHPbarUI(class Enemy* owner)
		: mOwner(owner)
		, mBarTex(nullptr)
		, mHPTex(nullptr)
		, mRenderHP(0.f)
		, mbRenderTrig(false)
	{
		mBarTex = ResourceManager::Load<Texture>(L"Monster_HP", L"..\\Resources\\UI\\MonsterLifeBar\\Monster_HP.bmp");
		mHPTex = ResourceManager::Load<Texture>(L"Monster_cHP", L"..\\Resources\\UI\\MonsterLifeBar\\Monster_cHP.bmp");	

		mRenderHP = (float)mOwner->GetHP();
	}

	EnemyHPbarUI::~EnemyHPbarUI()
	{
	}

	void EnemyHPbarUI::Initialize()
	{
		UI::Initialize();
	}

	void EnemyHPbarUI::Update()
	{
		// 일정시간 동안만 렌더링
		static float UIActivetime = 0.f;

		if (mbRenderTrig)
		{
			UIActivetime += Time::DeltaTime();
			if (UIActivetime > 3.f)
			{
				mbRenderTrig = false;
				UIActivetime = 0.f;
			}
		}

		if ((int)mRenderHP >= mOwner->GetHP())
			mRenderHP -= (float)Time::DeltaTime() * 100.f;	


		UI::Update();
	}

	void EnemyHPbarUI::Render(HDC hdc)
	{
		if (mbRenderTrig)
		{
			TransparentBlt(hdc, 180, 180, mBarTex->GetWidth(), mBarTex->GetHeight(), mBarTex->GetHdc()
				, 0, 0, mBarTex->GetWidth(), mBarTex->GetHeight(), RGB(255, 0, 255));

			TransparentBlt(hdc, 186, 181, (int)(mHPTex->GetWidth() * (mRenderHP / 100.f)), mHPTex->GetHeight(), mHPTex->GetHdc()
				, 0, 0, (int)(mHPTex->GetWidth() * (mRenderHP / 100.f)), mHPTex->GetHeight(), RGB(255, 0, 255));
		}

		UI::Render(hdc);
	}
}