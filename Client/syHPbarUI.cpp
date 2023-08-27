#include "syHPbarUI.h"
#include "syTexture.h"
#include "syAnimator.h"
#include "syResourceManager.h"
#include "syPlayer.h"
#include "syTransform.h"
#include "syApplication.h"
#include "sySceneManager.h"
#include "syTime.h"

namespace sy
{
	HPbarUI::HPbarUI()
		: mBarTex(nullptr)
		, mRedTex(nullptr)
		, mPinkTex(nullptr)
		, mDecreaseHP(0.f)
	{		
	}

	HPbarUI::~HPbarUI()
	{
	}

	void HPbarUI::Initialize()
	{
		mDecreaseHP = (float)SceneManager::GetPlayer()->GetCurHP();

		mBarTex = ResourceManager::Load<Texture>(L"HP_Bar", L"..\\Resources\\UI\\HpBar\\HP_Bar.bmp");
		mPinkTex = ResourceManager::Load<Texture>(L"HP_Pink", L"..\\Resources\\UI\\HpBar\\HP_Pink.bmp");
		mRedTex = ResourceManager::Load<Texture>(L"HP_Red", L"..\\Resources\\UI\\HpBar\\HP_Red.bmp");

		UI::Initialize();
	}

	void HPbarUI::Update()
	{
		static float time = 0.f;

		time += Time::DeltaTime();

		// 1초후에 감소
		if (time > 1.f)
		{
			if ((int)mDecreaseHP > SceneManager::GetPlayer()->GetCurHP())
				mDecreaseHP -= (float)Time::DeltaTime() * 15.f;
			else
			{
				time = 0.f;
				mDecreaseHP = (float)SceneManager::GetPlayer()->GetCurHP();
			}
		}


		UI::Update();
	}

	void HPbarUI::Render(HDC hdc)
	{
		Player* player = SceneManager::GetPlayer();
		int hp = player->GetCurHP();
		float fhp = (float)hp / player->GetMaxHP();
		
		TransparentBlt(hdc, 44, 176, mBarTex->GetWidth(), mBarTex->GetHeight(), mBarTex->GetHdc()
			, 0, 0, mBarTex->GetWidth(), mBarTex->GetHeight(), RGB(255, 0, 255));

		TransparentBlt(hdc, 50, 178, (int)(mRedTex->GetWidth() * (mDecreaseHP / player->GetMaxHP())), mRedTex->GetHeight(), mRedTex->GetHdc()
			, 0, 0, (int)(mRedTex->GetWidth() * (mDecreaseHP / player->GetMaxHP())), mRedTex->GetHeight(), RGB(255, 0, 255));

		TransparentBlt(hdc, 50, 178, (int)(mPinkTex->GetWidth() * fhp), mPinkTex->GetHeight(), mPinkTex->GetHdc()
			, 0, 0, (int)(mPinkTex->GetWidth() * fhp), mPinkTex->GetHeight(), RGB(255, 0, 255));

		UI::Render(hdc);
	}
}